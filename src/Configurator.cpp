#include "GameEvent.h"
#include "Configurator.h"
#include "GameGlobals.h"
#include "PathBuilder.h"
#include "AiStateMachine.h"
#include "Game.h"
#include "GameEvent.h"
#include "GamePalette.h"
#include "Grid.h"
#include "Tilemap.h"
#include "actions/DeleteGameObject.h"
#include "behaviors/CharacterMovement.h"
#include "behaviors/Coloring.h"
#include "behaviors/CharacterMovement.h"
#include "behaviors/Coloring.h"
#include "behaviors/DotsEating.h"
#include "behaviors/EnemyAnimation.h"
#include "behaviors/EnemyController.h"
#include "behaviors/EnemyEating.h"
#include "behaviors/EnemyOrientation.h"
#include "behaviors/PlayerAnimation.h"
#include "behaviors/PlayerController.h"
#include "behaviors/PlayerOrientation.h"
#include "behaviors/Energizing.h"
#include "behaviors/KillPlayer.h"
#include "behaviors/Spawning.h"
#include "objects/Enemy.h"
#include "objects/Energizer.h"
#include "objects/GhostEye.h"
#include "objects/Player.h"
#include "objects/Teleporter.h"
#include "personalities/Shadowing.h"
#include "personalities/Speeding.h"
#include "personalities/Shying.h"
#include "personalities/Poking.h"
#include <QGraphicsScene>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QHash>



Configurator::Configurator(QObject *parent) :
	QObject{parent}
{

}

void Configurator::configure(const QJsonObject &json)
{
	if (json.isEmpty())
		return;

	const QJsonObject &jsonPalette{json.value("palette").toObject()};
	const QJsonArray &jsonWalls{json.value("walls").toArray()};
	const QJsonArray &jsonDots{json.value("dots").toArray()};
	const QJsonObject &gridSize{json.value("gridSize").toObject()};
	const QJsonObject &cellSize{json.value("cellSize").toObject()};
	const QJsonArray &enemies{json.value("enemies").toArray()};
	int rows{gridSize.value("rows").toInt()};
	int columns{gridSize.value("columns").toInt()};
	qreal width{cellSize.value("width").toDouble()};
	qreal height{cellSize.value("height").toDouble()};

	Game &game{Game::ref()};
	auto *scene{game.scene()};
	auto *grid{game.grid()};
	auto *palette{game.palette()};

	configurePalette(jsonPalette);

	game.stateMachine()->setGameClock(game.clock());

	grid->setGridSize(rows, columns);
	grid->setCellSize(QSizeF(width, height));

	game.walls()->setGrid(grid);
	game.dots()->setGrid(grid);

	buildTilemap(game.walls(), jsonWalls, QPen(palette->color(CR_Wall), 4), QBrush(Qt::transparent));
	buildTilemap(game.dots(), jsonDots, QPen(Qt::transparent), palette->color(CR_Dot));

	game.walls()->setTile(13, 14, createTile(PathBuilder::TT_HLineLow, QPen(palette->color(CR_Door), 6), Qt::transparent));
	game.walls()->setTile(13, 15, createTile(PathBuilder::TT_HLineLow, QPen(palette->color(CR_Door), 6), Qt::transparent));

	setupPlayer(json.value("player").toObject());

	scene->addItem(createEnergizer({2, 4}));
	scene->addItem(createEnergizer({27, 4}));
	scene->addItem(createEnergizer({2, 24}));
	scene->addItem(createEnergizer({27, 24}));
	scene->addItem(createTeleporter(grid->mapFromGrid(15, 0), grid->mapFromGrid(15, 28)));
	scene->addItem(createTeleporter(grid->mapFromGrid(15, 29), grid->mapFromGrid(15, 2)));

	for (const auto &enemy : enemies)
		createEnemies(enemy.toObject());
}

void Configurator::configurePalette(const QJsonObject &jsonPalette)
{
	const auto &keys{jsonPalette.keys()};

	for (const auto &key : keys) {
		const QColor &color{jsonPalette.value(key).toString()};

		Game::ref().palette()->setColor(key2role(key), color);
	}
}

void Configurator::setupPlayer(const QJsonObject &jsonPlayer)
{
	auto *player{Game::ref().player()};
	qreal x{jsonPlayer.value("position").toObject().value("x").toDouble()};
	qreal y{jsonPlayer.value("position").toObject().value("y").toDouble()};
	auto *eventDotEaten{new GameEvent()};
	auto *eventEnemyEaten{new GameEvent()};
	auto *eventPlayerWins{new GameEvent()};
	auto *coloring{new Coloring(player)};
	auto *spawning{new Spawning(player)};
	auto *playerController{new PlayerController(player)};
	auto *movement{new CharacterMovement(player)};
	auto *orientation{new PlayerOrientation(player)};
	auto *dotsEating{new DotsEating(player)};
	auto *enemyEating{new EnemyEating(player)};
	auto *animation{new PlayerAnimation(player)};

	coloring->setColor(Game::ref().palette()->color(CR_Player));

	spawning->setPosition({x, y});

	playerController->setCharacterMovement(movement);
	playerController->setInputSystem(Game::ref().inputSystem());

	movement->setTilemap(Game::ref().walls());
	movement->setNextDirection(V2_LEFT);

	orientation->setMovement(movement);

	dotsEating->setTilemap(Game::ref().dots());
	dotsEating->setEvent(DotsEating::ET_DotEaten, eventDotEaten);
	dotsEating->setEvent(DotsEating::ET_PlayerWins, eventPlayerWins);

	enemyEating->setEvent(eventEnemyEaten);
	enemyEating->setEnabled(false);

	player->addBehavior(coloring);
	player->addBehavior(spawning);
	player->addBehavior(playerController);
	player->addBehavior(movement);
	player->addBehavior(orientation);
	player->addBehavior(dotsEating);
	player->addBehavior(enemyEating);
	player->addBehavior(animation);
	player->setSpeed(80);
	player->setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Player, 45));
	player->setPen(QPen(Qt::transparent));
	player->setBrush(Qt::white);
	player->reset();

	QObject::connect(eventDotEaten, &GameEvent::triggered, &Game::ref(), &Game::onDotEaten);
	QObject::connect(eventEnemyEaten, &GameEvent::triggered, &Game::ref(), &Game::onEnemyEaten);
	QObject::connect(eventPlayerWins, &GameEvent::triggered, &Game::ref(), &Game::onPlayerWins);
}

void Configurator::createEnemies(const QJsonObject &json)
{
	int role{key2role(json.value("name").toString())};
	const QColor &color{Game::ref().palette()->color(role)};
	const QJsonObject &position{json.value("position").toObject()};
	qreal posX{position.value("x").toDouble()};
	qreal posY{position.value("y").toDouble()};
	int direction{json.value("direction").toInt()};
	const QJsonObject &cell{json.value("scatterTargetCell").toObject()};
	int row{cell.value("row").toInt()};
	int column{cell.value("column").toInt()};
	auto *enemy{createEnemy({posX, posY}, color, direction)};
	auto *behavior{enemy->findBehavior(BT_EnemyController)};
	auto *controller{static_cast<EnemyController *>(behavior)};
	auto *personality{createPersonality(json.value("personality").toInt())};
	const auto &target{Game::ref().grid()->mapFromGrid(Vector2(column, row))};

	personality->setScatterTarget(target);
	personality->setPlayer(Game::ref().player());
	personality->setGrid(Game::ref().grid());

	if (personality->type() == AbstractPersonality::PT_Shying)
		static_cast<Shying *>(personality)->setPartner(Game::ref().enemies().at(0));

	enemy->setPersonality(personality);

	Game::ref().stateMachine()->addEnemyController(controller);
}

Enemy *Configurator::createEnemy(const QPointF &position, const QColor &color, int direction)
{
	auto *enemy{new Enemy()};
	auto *leftEye{new GhostEye(enemy)};
	auto *rightEye{new GhostEye(enemy)};

	leftEye->setPos(-6, -6);
	rightEye->setPos(6, -6);

	auto *coloring{new Coloring(enemy)};
	auto *spawning{new Spawning(enemy)};
	auto *movement{new CharacterMovement(enemy)};
	auto *orientation{new EnemyOrientation(enemy)};
	auto *enemyController{new EnemyController(enemy)};
	auto *animation{new EnemyAnimation(enemy)};
	auto *killPlayer{new KillPlayer(enemy)};
	auto *eventPlayerDies{new GameEvent()};

	coloring->setColor(color);

	spawning->setPosition(position);

	enemyController->setCharacterMovement(movement);
	enemyController->setGrid(Game::ref().grid());

	movement->setTilemap(Game::ref().walls());
	movement->setInitialDirection(dir2vec(direction));

	orientation->setMovement(movement);

	killPlayer->setEventPlayerDies(eventPlayerDies);

	enemy->addBehavior(coloring);
	enemy->addBehavior(spawning);
	enemy->addBehavior(enemyController);
	enemy->addBehavior(movement);
	enemy->addBehavior(orientation);
	enemy->addBehavior(animation);
	enemy->addBehavior(killPlayer);
	enemy->setSpeed(75);
	enemy->setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Enemy, 0));
	enemy->setPen(QPen(Qt::transparent));
	enemy->setBrush(color);

	connect(eventPlayerDies, &GameEvent::triggered, &Game::ref(), &Game::onPlayerDies);

	Game::ref().enemies().append(enemy);
	Game::ref().scene()->addItem(enemy);

	enemy->reset();

	return enemy;
}

GameObject *Configurator::createEnergizer(const QPoint &cell)
{
	auto *energizer{new Energizer()};

	energizer->setPos(Game::ref().grid()->mapFromGrid(cell.y(), cell.x()));

	return energizer;
}

GameObject *Configurator::createTeleporter(const QPointF &src, const QPointF &dst)
{
	auto *teleporter{new Teleporter()};

	teleporter->setup(src, dst);

	return teleporter;
}

AbstractPersonality *Configurator::createPersonality(int type)
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

void Configurator::buildTilemap(Tilemap *tilemap, const QJsonArray &matrix,
								const QPen &pen, const QBrush &brush)
{
	int m{0};

	for (const auto &row : matrix) {
		const QJsonArray &columns{row.toArray()};
		int n{0};

		for (const auto &column : columns) {
			const QJsonObject &element{column.toObject()};
			auto *tile{element.isEmpty() ? nullptr
										 : createTile(element["index"].toInt(),
													  pen, brush)};

			tilemap->setTile(m, n, tile);
			n++;
		}

		m++;
	}
}

QGraphicsItem *Configurator::createTile(int index, const QPen &pen, const QBrush &brush)
{
	auto *tile{new QGraphicsPathItem()};

	tile->setPath(PathBuilder::tilePath(PathBuilder::TileType(index)));
	tile->setPen(pen);
	tile->setBrush(brush);

	return tile;
}

Vector2 Configurator::dir2vec(int direction) const
{
	return QHash<int, Vector2>{{0, V2_LEFT}, {1, V2_UP}, {2, V2_RIGHT},
							   {3, V2_DOWN}}.value(direction);
}

int Configurator::key2role(const QString &key) const
{
	return QHash<QString, int>{{"Player", CR_Player},
							   {"PlayerEnergized", CR_PlayerEnergized},
							   {"Blinky", CR_Blinky},
							   {"Inky", CR_Inky},
							   {"Pinky", CR_Pinky},
							   {"Clyde", CR_Clyde},
							   {"EnemyFrightened", CR_EnemyFrightened},
							   {"Wall", CR_Wall},
							   {"Door", CR_Door},
							   {"Dot", CR_Dot},
							   {"Energizer", CR_Energizer}}.value(key);
}
