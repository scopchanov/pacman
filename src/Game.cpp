#include "Game.h"
#include "Message.h"
#include "PathBuilder.h"
#include "StartupSequence.h"
#include "engine/AiStateMachine.h"
#include "engine/GameController.h"
#include "engine/GameEvent.h"
#include "engine/GameScene.h"
#include "engine/GameTimer.h"
#include "engine/Ghost.h"
#include "engine/Grid.h"
#include "engine/Pacman.h"
#include "engine/SoundEngine.h"
#include "engine/Teleporter.h"
#include "engine/Tile.h"
#include "engine/Tilemap.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/EnemyAnimation.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/behaviors/EnemyOrientation.h"
#include "engine/behaviors/KillPlayer.h"
#include "engine/personalities/Shadowing.h"
#include "engine/personalities/Speeding.h"
#include "engine/personalities/Shying.h"
#include "engine/personalities/Poking.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

Game::Game(QObject *parent) :
	QObject(parent),
	_gameController{new GameController(this)},
	_soundEngine{new SoundEngine(this)},
	_scene{new GameScene(this)},
	_grid{new Grid()},
	_walls{new Tilemap()},
	_dots{new Tilemap()},
	_stateMachine{new AiStateMachine(this)},
	_pacman{new Pacman()}
{
	_gameController->gameTimer()->setScene(_scene);

	connect(_soundEngine, &SoundEngine::funeralMarchPlayed, this, &Game::onFuneralMarchPlayed);
}

GameController *Game::gameController() const
{
	return _gameController;
}

GameScene *Game::scene() const
{
	return _scene;
}

Grid *Game::grid() const
{
	return _grid;
}

Tilemap *Game::walls() const
{
	return _walls;
}

Tilemap *Game::dots() const
{
	return _dots;
}

void Game::configure(const QJsonObject &json)
{
	const QJsonArray &wallMatrix{json.value("walls").toArray()};
	const QJsonArray &dotMatrix{json.value("dots").toArray()};
	const QJsonObject &gridSize{json.value("gridSize").toObject()};
	const QJsonObject &cellSize{json.value("cellSize").toObject()};
	const QJsonObject &player{json.value("player").toObject()};
	const QJsonArray &enemies{json.value("enemies").toArray()};
	int rows{gridSize.value("rows").toInt()};
	int columns{gridSize.value("columns").toInt()};
	qreal width{cellSize.value("width").toDouble()};
	qreal height{cellSize.value("height").toDouble()};
	qreal playerX{player.value("position").toObject().value("x").toDouble()};
	qreal playerY{player.value("position").toObject().value("y").toDouble()};

	_grid->setGridSize(rows, columns);
	_grid->setCellSize(QSizeF(width, height));

	_walls->setGrid(_grid);
	_dots->setGrid(_grid);

	buildTilemap(_walls, wallMatrix, QPen(QColor(0x1976D2), 4), QBrush(Qt::transparent));
	buildTilemap(_dots, dotMatrix, QPen(Qt::transparent), QBrush(0x999999));

	_walls->setTile(13, 14, createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), QBrush(Qt::transparent)));
	_walls->setTile(13, 15, createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), QBrush(Qt::transparent)));

	_pacman->setSpawnPosition({playerX, playerY});
	_pacman->setup(this);

	_scene->addItem(_pacman);
	_scene->addItem(_walls);
	_scene->addItem(_dots);

	createEnemies(enemies);

	_stateMachine->setGameTimer(gameController()->gameTimer());
	_scene->addItem(createTeleporter(_grid->cellPosition(15, 0), _grid->cellPosition(15, 28)));
	_scene->addItem(createTeleporter(_grid->cellPosition(15, 29), _grid->cellPosition(15, 2)));
}

void Game::start()
{
	auto *sequence{new StartupSequence(this)};

	_scene->addItem(sequence->message());

	connect(sequence, &StartupSequence::go, _gameController, &GameController::start);

	sequence->start();
}

void Game::buildTilemap(Tilemap *tilemap, const QJsonArray &matrix,
							  const QPen &pen, const QBrush &brush)
{
	int m{0};

	for (const auto &row : matrix) {
		const QJsonArray &columns{row.toArray()};
		int n{0};

		for (const auto &column : columns) {
			const QJsonObject &element{column.toObject()};
			Tile *tile{element.isEmpty() ? nullptr
										 : createTile(element["index"].toInt(),
													  pen, brush)};

			tilemap->setTile(m, n, tile);
			n++;
		}

		m++;
	}
}

Tile *Game::createTile(int index, const QPen &pen, const QBrush &brush)
{
	auto *tile{new Tile()};

	tile->setPath(PathBuilder::tilePath(PathBuilder::TileType(index)));
	tile->setPen(pen);
	tile->setBrush(brush);

	return tile;
}

void Game::createEnemies(const QJsonArray &enemies)
{
	for (const auto &record : enemies) {
		const QJsonObject &json{record.toObject()};
		const QJsonObject &position{json.value("position").toObject()};
		qreal posX{position.value("x").toDouble()};
		qreal posY{position.value("y").toDouble()};
		const QString &color{json.value("color").toString()};
		const QJsonObject &cell{json.value("scatterTargetCell").toObject()};
		int row{cell.value("row").toInt()};
		int column{cell.value("column").toInt()};
		auto *enemy{createEnemy({posX, posY}, color)};
		auto *behavior{enemy->findBehavior(AbstractBehavior::BT_EnemyController)};
		auto *controller{static_cast<EnemyController *>(behavior)};
		auto *personality{createPersonality(json.value("personality").toInt())};

		personality->setScatterTarget(_grid->cellPosition(Vector2(column, row)));
		personality->setPlayer(_pacman);
		personality->setGrid(_grid);

		if (personality->type() == AbstractPersonality::PT_Shying)
			static_cast<Shying *>(personality)->setPartner(_ghosts.at(0));

		enemy->setPersonality(personality);

		_stateMachine->addEnemyController(controller);
	}
}

Ghost *Game::createEnemy(const QPointF &position, const QColor &color)
{
	auto *ghost{new Ghost()};

	ghost->setSpawnPosition(position);

	auto *movement{new CharacterMovement(ghost)};
	auto *orientation{new EnemyOrientation(ghost)};
	auto *enemyController{new EnemyController(ghost)};
	auto *animation{new EnemyAnimation(ghost)};
	auto *killPlayer{new KillPlayer(ghost)};
	auto *eventPlayerDies{new GameEvent(this)};

	enemyController->setCharacterMovement(movement);
	enemyController->setPlayer(_pacman);	
	enemyController->setGrid(_grid);

	movement->setGameTimer(_gameController->gameTimer());
	movement->setTilemap(_walls);
	movement->setMovingSpeed(150);
	movement->setNextDirection(Vector2(-1, 0));

	orientation->setMovement(movement);

	animation->setGameTimer(_gameController->gameTimer());
	animation->setFrameTime(20);

	killPlayer->setGameTimer(_gameController->gameTimer());
	killPlayer->setPlayer(_pacman);
	killPlayer->setEventPlayerDies(eventPlayerDies);

	ghost->addBehavior(enemyController);
	ghost->addBehavior(movement);
	ghost->addBehavior(orientation);
	ghost->addBehavior(animation);
	ghost->addBehavior(killPlayer);

	ghost->setBrush(color);

	connect(eventPlayerDies, &GameEvent::triggered, this, &Game::onPlayerDies);

	_ghosts.append(ghost);
	_scene->addItem(ghost);

	return ghost;
}

GameObject *Game::createTeleporter(const QPointF &src, const QPointF &dst)
{
	auto *teleporter{new Teleporter()};

	teleporter->setup(src, dst);

	return teleporter;
}

AbstractPersonality *Game::createPersonality(int type)
{
	switch (type) {
	case AbstractPersonality::PT_Shadowing:
		return new Shadowing();
	case AbstractPersonality::PT_Speeding:
		return new Speeding();
	case AbstractPersonality::PT_Shying:
		return new Shying();
	case AbstractPersonality::PT_Poking:
		return new Poking();
	default:
		return nullptr;
	}
}

void Game::reset()
{
	_stateMachine->reset();
	_scene->reset();
	start();
}

void Game::gameOver()
{
	qDebug() << "Game Over!";
}

void Game::onDotEaten()
{
	_gameController->increaseScore(1);
	_soundEngine->playEffect(SoundEngine::SND_DotEaten);
}

void Game::onPlayerWins()
{
	_gameController->gameTimer()->stop();
	_soundEngine->playEffect(SoundEngine::SND_PlayerWins);
}

void Game::onPlayerDies()
{
	_gameController->gameTimer()->stop();
	_soundEngine->playEffect(SoundEngine::SND_PlayerDies);
}

void Game::onFuneralMarchPlayed()
{
	if (_gameController->lifesLeft()) {
		_gameController->removeLife();
		reset();
	} else {
		gameOver();
	}
}
