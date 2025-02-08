#include "Game.h"
#include "GameController.h"
#include "SoundEngine.h"
#include "Message.h"
#include "PathBuilder.h"
#include "StartupSequence.h"
#include "engine/AiStateMachine.h"
#include "engine/Enemy.h"
#include "engine/GameTimer.h"
#include "engine/GameEvent.h"
#include "engine/Grid.h"
#include "engine/Pacman.h"
#include "engine/Scene.h"
#include "engine/Tile.h"
#include "engine/Tilemap.h"
#include "engine/behaviors/PlayerController.h"
#include "engine/behaviors/PlayerOrientation.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/DotsEating.h"
#include "engine/behaviors/EnemyAnimation.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/behaviors/KillPlayer.h"
#include "engine/behaviors/PlayerAnimation.h"
#include "engine/behaviors/Teleporting.h"
#include "engine/personalities/Shadowing.h"
#include "engine/personalities/Speeding.h"
#include "engine/personalities/Shying.h"
#include "engine/personalities/Poking.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

Game::Game(QObject *parent) :
	QObject(parent),
	m_gameController{new GameController(this)},
	m_soundEngine{new SoundEngine(this)},
	m_scene{new Scene(this)}
{
	m_gameController->gameTimer()->setScene(m_scene);
}

GameController *Game::gameController() const
{
	return m_gameController;
}

Scene *Game::scene() const
{
	return m_scene;
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
	auto *tmWalls{new Tilemap()};
	auto *tmDots{new Tilemap()};
	auto *stateMachine{new AiStateMachine(this)};

	grid->setGridSize(rows, columns);
	grid->setCellSize(QSizeF(width, height));

	tmWalls->setGrid(grid);
	tmDots->setGrid(grid);

	buildTilemap(tmWalls, wallMatrix, QPen(QColor(0x1976D2), 4), QBrush(Qt::transparent));
	buildTilemap(tmDots, dotMatrix, QPen(Qt::transparent), QBrush(0x999999));

	tmWalls->setTile(13, 14, createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), QBrush(Qt::transparent)));
	tmWalls->setTile(13, 15, createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), QBrush(Qt::transparent)));

	auto *pacman{createPacman(tmWalls, tmDots)};
	auto *blinky{createEnemy(tmWalls, pacman, QPointF(360, 300), 0xF44336, grid->cellPosition(0, 28), grid)};
	auto *inky{createEnemy(tmWalls, pacman, QPointF(312, 372), 0x82B1FF,  grid->cellPosition(32, 28), grid)};
	auto *pinky{createEnemy(tmWalls, pacman, QPointF(360, 372), 0xFF80AB,  grid->cellPosition(0, 1), grid)};
	auto *clyde{createEnemy(tmWalls, pacman, QPointF(408, 372), 0xFFC107,  grid->cellPosition(32, 1), grid)};

	auto *shadowing{new Shadowing(this)};
	auto *speeding{new Speeding(this)};
	auto *shying{new Shying(this)};
	auto *poking{new Poking(this)};

	shadowing->setPlayer(pacman);
	speeding->setPlayer(pacman);
	speeding->setGrid(grid);
	shying->setPlayer(pacman);
	shying->setGrid(grid);
	shying->setEnemy(blinky);
	poking->setPlayer(pacman);
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

	m_scene->addItem(pacman);
	m_scene->addItem(tmWalls);
	m_scene->addItem(tmDots);
	m_scene->addItem(blinky);
	m_scene->addItem(pinky);
	m_scene->addItem(inky);
	m_scene->addItem(clyde);
	m_scene->addItem(createTeleporter(grid->cellPosition(15, 0), grid->cellPosition(15, 28)));
	m_scene->addItem(createTeleporter(grid->cellPosition(15, 29), grid->cellPosition(15, 2)));
}

void Game::start()
{
	auto *sequence{new StartupSequence(this)};

	m_scene->addItem(sequence->message());

	connect(sequence, &StartupSequence::go, m_gameController, &GameController::start);

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
	auto *tile{new Tile(	)};

	tile->setPath(PathBuilder::tilePath(PathBuilder::TileType(index)));
	tile->setPen(pen);
	tile->setBrush(brush);

	return tile;
}

GameObject *Game::createPacman(Tilemap *tmWalls, Tilemap *tmDots)
{
	auto *gameTimer{m_gameController->gameTimer()};
	auto *pacman{new Pacman()};
	auto *eventDotEaten{new GameEvent(this)};
	auto *eventPlayerWins{new GameEvent(this)};

	pacman->playerController()->setInputSystem(m_scene->inputSystem());

	pacman->movement()->setGameTimer(gameTimer);
	pacman->movement()->setTilemap(tmWalls);

	pacman->dotsEating()->setGameTimer(gameTimer);
	pacman->dotsEating()->setTilemap(tmDots);
	pacman->dotsEating()->setEvent(DotsEating::ET_DotEaten, eventDotEaten);
	pacman->dotsEating()->setEvent(DotsEating::ET_PlayerWins, eventPlayerWins);

	pacman->animation()->setGameTimer(gameTimer);

	connect(eventDotEaten, &GameEvent::triggered, this, &Game::onPointEaten);
	connect(eventPlayerWins, &GameEvent::triggered, this, &Game::onPlayerWins);

	return pacman;
}

GameObject *Game::createEnemy(Tilemap *tmLayout, GameObject *player, const QPointF &position, const QColor &color, const QPointF &scatterTarget, Grid *grid)
{
	auto *enemy{new GameObject()};

	enemy->setPos(position);

	auto *movement{new CharacterMovement(enemy)};
	// auto *orientation{new PlayerOrientation(enemy)};
	auto *enemyController{new EnemyController(enemy)};
	auto *animation{new EnemyAnimation(enemy)};
	auto *killPlayer{new KillPlayer(enemy)};
	auto *eventPlayerDies{new GameEvent(this)};

	enemyController->setCharacterMovement(movement);
	enemyController->setPlayer(player);
	enemyController->setScatterTarget(scatterTarget);
	enemyController->setGrid(grid);

	movement->setGameTimer(m_gameController->gameTimer());
	movement->setTilemap(tmLayout);
	movement->setMovingSpeed(150);
	movement->setNextDirection(Vector2(-1, 0));

	// orientation->setMovement(movement);

	animation->setGameTimer(m_gameController->gameTimer());

	killPlayer->setGameTimer(m_gameController->gameTimer());
	killPlayer->setPlayer(player);
	killPlayer->setEventPlayerDies(eventPlayerDies);

	enemy->addBehavior(enemyController);
	enemy->addBehavior(movement);
	// enemy->addBehavior(orientation);
	enemy->addBehavior(animation);
	enemy->addBehavior(killPlayer);

	enemy->setPath(PathBuilder::enemyPath(0));
	enemy->setPen(QPen(Qt::transparent));
	enemy->setBrush(color);

	connect(eventPlayerDies, &GameEvent::triggered, this, &Game::onPlayerDies);

	return enemy;
}

GameObject *Game::createTeleporter(const QPointF &src, const QPointF &dst)
{
	auto *teleporter{new GameObject()};
	auto *teleporting{new Teleporting(teleporter)};

	teleporting->setDestination(dst);

	teleporter->setPos(src);
	teleporter->addBehavior(teleporting);

	teleporter->setPath(PathBuilder::teleporterPath());
	teleporter->setPen(QPen(Qt::transparent));
	teleporter->setBrush(Qt::transparent);
	teleporter->setFlag(QGraphicsItem::ItemHasNoContents);

	return teleporter;
}

void Game::onPointEaten()
{
	m_gameController->increaseScore(1);
	m_soundEngine->playEffect(SoundEngine::SND_DotEaten);
}

void Game::onPlayerWins()
{
	m_gameController->gameTimer()->stop();
	m_soundEngine->playEffect(SoundEngine::SND_PlayerWins);
}

void Game::onPlayerDies()
{
	m_gameController->gameTimer()->stop();
	m_soundEngine->playEffect(SoundEngine::SND_PlayerDies);
	m_gameController->removeLife();
}
