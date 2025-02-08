#include "Game.h"
#include "GameController.h"
#include "SoundEngine.h"
#include "Message.h"
#include "PathBuilder.h"
#include "StartupSequence.h"
#include "engine/AiStateMachine.h"
#include "engine/GameTimer.h"
#include "engine/GameEvent.h"
#include "engine/Grid.h"
#include "engine/Pacman.h"
#include "engine/Scene.h"
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
	_scene{new Scene(this)},
	_walls{new Tilemap()},
	_dots{new Tilemap()},
	_pacman{new Pacman()}
{
	_gameController->gameTimer()->setScene(_scene);
}

GameController *Game::gameController() const
{
	return _gameController;
}

Scene *Game::scene() const
{
	return _scene;
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
	int rows{gridSize.value("rows").toInt()};
	int columns{gridSize.value("columns").toInt()};
	qreal width{cellSize.value("width").toDouble()};
	qreal height{cellSize.value("height").toDouble()};
	auto *grid{new Grid()};
	auto *stateMachine{new AiStateMachine(this)};

	grid->setGridSize(rows, columns);
	grid->setCellSize(QSizeF(width, height));

	_walls->setGrid(grid);
	_dots->setGrid(grid);

	buildTilemap(_walls, wallMatrix, QPen(QColor(0x1976D2), 4), QBrush(Qt::transparent));
	buildTilemap(_dots, dotMatrix, QPen(Qt::transparent), QBrush(0x999999));

	_walls->setTile(13, 14, createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), QBrush(Qt::transparent)));
	_walls->setTile(13, 15, createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), QBrush(Qt::transparent)));

	_pacman->setup(this);

	auto *blinky{createEnemy(QPointF(360, 300), 0xF44336, grid->cellPosition(0, 28), grid)};
	auto *inky{createEnemy(QPointF(312, 372), 0x82B1FF,  grid->cellPosition(32, 28), grid)};
	auto *pinky{createEnemy(QPointF(360, 372), 0xFF80AB,  grid->cellPosition(0, 1), grid)};
	auto *clyde{createEnemy(QPointF(408, 372), 0xFFC107,  grid->cellPosition(32, 1), grid)};

	auto *shadowing{new Shadowing(this)};
	auto *speeding{new Speeding(this)};
	auto *shying{new Shying(this)};
	auto *poking{new Poking(this)};

	shadowing->setPlayer(_pacman);
	speeding->setPlayer(_pacman);
	speeding->setGrid(grid);
	shying->setPlayer(_pacman);
	shying->setGrid(grid);
	shying->setEnemy(blinky);
	poking->setPlayer(_pacman);
	poking->setEnemy(clyde);
	poking->setGrid(grid);

	auto *bec{static_cast<EnemyController *>(blinky->findBehavior(AbstractBehavior::BT_EnemyController))};
	auto *pec{static_cast<EnemyController *>(pinky->findBehavior(AbstractBehavior::BT_EnemyController))};
	auto *iec{static_cast<EnemyController *>(inky->findBehavior(AbstractBehavior::BT_EnemyController))};
	auto *cec{static_cast<EnemyController *>(clyde->findBehavior(AbstractBehavior::BT_EnemyController))};

	bec->setPersonality(shadowing);
	pec->setPersonality(speeding);
	iec->setPersonality(shying);
	cec->setPersonality(poking);

	stateMachine->setGameTimer(gameController()->gameTimer());
	stateMachine->addEnemyController(bec);
	stateMachine->addEnemyController(pec);
	stateMachine->addEnemyController(iec);
	stateMachine->addEnemyController(cec);

	_scene->addItem(_pacman);
	_scene->addItem(_walls);
	_scene->addItem(_dots);
	_scene->addItem(blinky);
	_scene->addItem(pinky);
	_scene->addItem(inky);
	_scene->addItem(clyde);
	_scene->addItem(createTeleporter(grid->cellPosition(15, 0), grid->cellPosition(15, 28)));
	_scene->addItem(createTeleporter(grid->cellPosition(15, 29), grid->cellPosition(15, 2)));
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

GameObject *Game::createEnemy(const QPointF &position, const QColor &color, const QPointF &scatterTarget, Grid *grid)
{
	auto *enemy{new GameObject()};

	enemy->setPos(position);

	auto *movement{new CharacterMovement(enemy)};
	auto *orientation{new EnemyOrientation(enemy)};
	auto *enemyController{new EnemyController(enemy)};
	auto *animation{new EnemyAnimation(enemy)};
	auto *killPlayer{new KillPlayer(enemy)};
	auto *eventPlayerDies{new GameEvent(this)};

	enemyController->setCharacterMovement(movement);
	enemyController->setPlayer(_pacman);
	enemyController->setScatterTarget(scatterTarget);
	enemyController->setGrid(grid);

	movement->setGameTimer(_gameController->gameTimer());
	movement->setTilemap(_walls);
	movement->setMovingSpeed(150);
	movement->setNextDirection(Vector2(-1, 0));

	orientation->setMovement(movement);

	animation->setGameTimer(_gameController->gameTimer());

	killPlayer->setGameTimer(_gameController->gameTimer());
	killPlayer->setPlayer(_pacman);
	killPlayer->setEventPlayerDies(eventPlayerDies);

	enemy->addBehavior(enemyController);
	enemy->addBehavior(movement);
	enemy->addBehavior(orientation);
	enemy->addBehavior(animation);
	enemy->addBehavior(killPlayer);

	enemy->setPath(PathBuilder::enemyPath(0));
	enemy->setPen(QPen(Qt::transparent));
	enemy->setBrush(color);

	auto *leftEye{new QGraphicsEllipseItem(QRectF(-10, -11, 8, 10), enemy)};
	auto *rightEye{new QGraphicsEllipseItem(QRectF(2, -11, 8, 10), enemy)};
	auto *leftEyeBall{new QGraphicsEllipseItem(QRectF(-9, -6, 6, 6), enemy)};
	auto *rightEyeBall{new QGraphicsEllipseItem(QRectF(3, -6, 6, 6), enemy)};

	leftEye->setPen(QPen(Qt::transparent));
	leftEye->setBrush(Qt::white);

	leftEyeBall->setPen(QPen(Qt::transparent));
	leftEyeBall->setBrush(Qt::black);

	rightEye->setPen(QPen(Qt::transparent));
	rightEye->setBrush(Qt::white);

	rightEyeBall->setPen(QPen(Qt::transparent));
	rightEyeBall->setBrush(Qt::black);

	connect(eventPlayerDies, &GameEvent::triggered, this, &Game::onPlayerDies);

	return enemy;
}

GameObject *Game::createTeleporter(const QPointF &src, const QPointF &dst)
{
	auto *teleporter{new Teleporter()};

	teleporter->setup(src, dst);

	return teleporter;
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
	_gameController->removeLife();
}
