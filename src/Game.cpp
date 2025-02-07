#include "Game.h"
#include "GameController.h"
#include "SoundEngine.h"
#include "Message.h"
#include "PathBuilder.h"
#include "StartupSequence.h"
#include "engine/AiStateMachine.h"
#include "engine/GameTimer.h"
#include "engine/Scene.h"
#include "engine/behaviors/PlayerController.h"
#include "engine/behaviors/PlayerOrientation.h"
// #include "engine/behaviors/CameraFollow.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/DotsEating.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/behaviors/KillPlayer.h"
#include "engine/behaviors/PlayerAnimation.h"
#include "engine/behaviors/Teleporting.h"
#include "engine/GameEvent.h"
#include "engine/Grid.h"
#include "engine/Tile.h"
#include "engine/Tilemap.h"
#include "engine/personalities/Shadowing.h"
#include "engine/personalities/Speeding.h"
#include "engine/personalities/Shying.h"
#include "engine/personalities/Poking.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QGraphicsSvgItem>

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
	auto *tmLayout{new Tilemap()};
	auto *tmDots{new Tilemap()};
	auto *stateMachine{new AiStateMachine(this)};

	grid->setGridSize(rows, columns);
	grid->setCellSize(QSizeF(width, height));

	tmLayout->setGrid(grid);
	tmDots->setGrid(grid);

	buildTilemap(tmLayout, wallMatrix, QPen(QColor(0x1976D2), 4), QBrush(Qt::transparent));
	buildTilemap(tmDots, dotMatrix, QPen(Qt::transparent), QBrush(0x999999));

	auto *player{createPlayer(tmLayout, tmDots)};
	auto *blinky{createEnemy(tmLayout, player, QPointF(360, 300), "blinky", grid->cellPosition(32, 28))};
	auto *inky{createEnemy(tmLayout, player, QPointF(312, 372), "inky",  grid->cellPosition(0, 28))};
	auto *pinky{createEnemy(tmLayout, player, QPointF(360, 372), "pinky",  grid->cellPosition(32, 1))};
	auto *clyde{createEnemy(tmLayout, player, QPointF(408, 372), "clyde",  grid->cellPosition(0, 1))};

	auto *shadowing{new Shadowing(this)};
	auto *speeding{new Speeding(this)};
	auto *shying{new Shying(this)};
	auto *poking{new Poking(this)};

	shadowing->setPlayer(player);
	speeding->setPlayer(player);
	speeding->setGrid(grid);
	shying->setPlayer(player);
	shying->setGrid(grid);
	shying->setEnemy(blinky);
	poking->setPlayer(player);
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

	m_scene->addItem(player);
	m_scene->addItem(tmLayout);
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
	auto *tile{new Tile()};

	tile->setPath(PathBuilder::tilePath(PathBuilder::TileType(index)));
	tile->setPen(pen);
	tile->setBrush(brush);

	return tile;
}

GameObject *Game::createPlayer(Tilemap *tmLayout, Tilemap *tmDots)
{
	auto *player{new GameObject()};

	player->setPos(360, 588);

	auto *movement{new CharacterMovement(player)};
	auto *orientation{new PlayerOrientation(player)};
	auto *dotsEating{new DotsEating(player)};
	// auto *cameraFollow{new CameraFollow(player)};
	auto *playerController{new PlayerController(player)};
	auto *animation{new PlayerAnimation(player)};
	auto *eventDotEaten{new GameEvent(this)};
	auto *eventPlayerWins{new GameEvent(this)};

	playerController->setCharacterMovement(movement);
	playerController->setInputSystem(m_scene->inputSystem());

	movement->setGameTimer(m_gameController->gameTimer());
	movement->setTilemap(tmLayout);
	movement->setMovingSpeed(200);
	movement->setNextDirection(Vector2(-1, 0));

	orientation->setMovement(movement);

	dotsEating->setGameTimer(m_gameController->gameTimer());
	dotsEating->setTilemap(tmDots);
	dotsEating->setEvent(DotsEating::ET_DotEaten, eventDotEaten);
	dotsEating->setEvent(DotsEating::ET_PlayerWins, eventPlayerWins);

	// cameraFollow->setView(m_scene->views().at(0));

	animation->setGameTimer(m_gameController->gameTimer());

	player->addBehavior(playerController);
	player->addBehavior(movement);
	player->addBehavior(orientation);
	player->addBehavior(animation);
	// player->addBehavior(cameraFollow);
	player->addBehavior(dotsEating);

	player->setPath(PathBuilder::playerPath(45));
	player->setPen(QPen(Qt::transparent));
	player->setBrush(Qt::white);

	connect(eventDotEaten, &GameEvent::triggered, this, &Game::onPointEaten);
	connect(eventPlayerWins, &GameEvent::triggered, this, &Game::onPlayerWins);

	return player;
}

GameObject *Game::createEnemy(Tilemap *tmLayout, GameObject *player, const QPointF &position, const QString &color, const QPointF &scatterTarget)
{
	auto *enemy{new GameObject()};

	enemy->setPos(position);

	auto *movement{new CharacterMovement(enemy)};
	// auto *orientation{new PlayerOrientation(enemy)};
	auto *enemyController{new EnemyController(enemy)};
	// auto *animation{new PlayerAnimation(enemy)};
	auto *killPlayer{new KillPlayer(enemy)};
	auto *eventPlayerDies{new GameEvent(this)};

	enemyController->setCharacterMovement(movement);
	enemyController->setPlayer(player);
	enemyController->setScatterTarget(scatterTarget);

	movement->setGameTimer(m_gameController->gameTimer());
	movement->setTilemap(tmLayout);
	movement->setMovingSpeed(150);
	movement->setNextDirection(Vector2(-1, 0));

	// orientation->setMovement(movement);

	// animation->setGameTimer(m_gameTimer);

	killPlayer->setGameTimer(m_gameController->gameTimer());
	killPlayer->setPlayer(player);
	killPlayer->setEventPlayerDies(eventPlayerDies);

	enemy->addBehavior(enemyController);
	enemy->addBehavior(movement);
	// enemy->addBehavior(orientation);
	// enemy->addBehavior(animation);
	enemy->addBehavior(killPlayer);


	enemy->setPath(PathBuilder::enemyPath());
	enemy->setPen(QPen(Qt::transparent));
	enemy->setBrush(Qt::transparent);
	enemy->setFlag(QGraphicsItem::ItemHasNoContents);

	auto *svg{new QGraphicsSvgItem(":/pix/svg/enemy-" + color + ".svg")};

	svg->setParentItem(enemy);
	svg->setPos(-24, -24);

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
