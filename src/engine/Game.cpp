#include "Game.h"
#include "GameController.h"
#include "SoundEngine.h"
#include "Message.h"
#include "PathBuilder.h"
#include "StartupSequence.h"
#include "engine/AiStateMachine.h"
#include "engine/GameTimer.h"
#include "engine/GameEvent.h"
#include "engine/Ghost.h"
#include "engine/Grid.h"
#include "engine/Pacman.h"
#include "engine/GameScene.h"
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

	auto *blinky{createEnemy({360, 300}, 0xF44336, Vector2(28, 0))};
	auto *inky{createEnemy({312, 372}, 0x82B1FF,  Vector2(28, 32))};
	auto *pinky{createEnemy({360, 372}, 0xFF80AB,  Vector2(1, 0))};
	auto *clyde{createEnemy({408, 372}, 0xFFC107,  Vector2(1, 32))};

	auto *shadowing{new Shadowing(this)};
	auto *speeding{new Speeding(this)};
	auto *shying{new Shying(this)};
	auto *poking{new Poking(this)};

	shadowing->setPlayer(_pacman);
	speeding->setPlayer(_pacman);
	speeding->setGrid(_grid);

	shying->setPlayer(_pacman);
	shying->setGrid(_grid);
	shying->setEnemy(blinky);

	poking->setPlayer(_pacman);
	poking->setEnemy(clyde);
	poking->setGrid(_grid);

	auto *bec{static_cast<EnemyController *>(blinky->findBehavior(AbstractBehavior::BT_EnemyController))};
	auto *pec{static_cast<EnemyController *>(pinky->findBehavior(AbstractBehavior::BT_EnemyController))};
	auto *iec{static_cast<EnemyController *>(inky->findBehavior(AbstractBehavior::BT_EnemyController))};
	auto *cec{static_cast<EnemyController *>(clyde->findBehavior(AbstractBehavior::BT_EnemyController))};

	bec->setPersonality(shadowing);
	pec->setPersonality(speeding);
	iec->setPersonality(shying);
	cec->setPersonality(poking);

	_stateMachine->setGameTimer(gameController()->gameTimer());
	_stateMachine->addEnemyController(bec);
	_stateMachine->addEnemyController(pec);
	_stateMachine->addEnemyController(iec);
	_stateMachine->addEnemyController(cec);

	_scene->addItem(_pacman);
	_scene->addItem(_walls);
	_scene->addItem(_dots);
	_scene->addItem(blinky);
	_scene->addItem(pinky);
	_scene->addItem(inky);
	_scene->addItem(clyde);
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

Ghost *Game::createEnemy(const QPointF &position, const QColor &color, const Vector2 &scatterTargetCell)
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
	enemyController->setScatterTarget(_grid->cellPosition(scatterTargetCell));
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

	ghost->setPath(PathBuilder::enemyPath(0));
	ghost->setPen(QPen(Qt::transparent));
	ghost->setBrush(color);

	connect(eventPlayerDies, &GameEvent::triggered, this, &Game::onPlayerDies);

	_ghosts.append(ghost);

	return ghost;
}

GameObject *Game::createTeleporter(const QPointF &src, const QPointF &dst)
{
	auto *teleporter{new Teleporter()};

	teleporter->setup(src, dst);

	return teleporter;
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
