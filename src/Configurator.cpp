#include "Configurator.h"
#include "AiStateMachine.h"
#include "Factory.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "GamePalette.h"
#include "Grid.h"
#include "PathBuilder.h"
#include "Tilemap.h"
#include "BehaviorBuilder.h"
#include "actions/DeleteGameObject.h"
#include "behaviors/Moving.h"
#include "behaviors/EnemyControlling.h"
#include "objects/Enemy.h"
#include "objects/Energizer.h"
#include "objects/GhostEye.h"
#include "objects/Player.h"
#include "objects/Teleporter.h"
#include "personalities/Shying.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

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
	auto *scene{Game::ref().level()};
	auto *grid{Game::ref().level()->grid()};
	auto *palette{Game::ref().palette()};
	auto *walls{Game::ref().level()->walls()};
	auto *dots{Game::ref().level()->dots()};

	configurePalette(jsonPalette);

	grid->setGridSize(rows, columns);
	grid->setCellSize(QSizeF(width, height));

	walls->setGrid(grid);
	dots->setGrid(grid);

	buildTilemap(walls, jsonWalls, QPen(palette->color(CR_Wall), 4), QBrush(Qt::transparent));
	buildTilemap(dots, jsonDots, QPen(Qt::transparent), palette->color(CR_Dot));

	walls->setTile(13, 14, createTile(PathBuilder::TT_HLineLow, QPen(palette->color(CR_Door), 6), Qt::transparent));
	walls->setTile(13, 15, createTile(PathBuilder::TT_HLineLow, QPen(palette->color(CR_Door), 6), Qt::transparent));

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
	auto *player{Game::ref().level()->player()};
	qreal x{jsonPlayer.value("position").toObject().value("x").toDouble()};
	qreal y{jsonPlayer.value("position").toObject().value("y").toDouble()};
	auto *moving{new Moving(player)};

	moving->setTilemap(Game::ref().level()->walls());
	moving->setNextDirection(V2_LEFT);

	BehaviorBuilder builder;

	builder.setGameObject(player);
	builder.addColoring(Game::ref().palette()->color(CR_Player));
	builder.addSpawning({x, y});

	player->addBehavior(moving);

	builder.addControlling(OBJ_Player);
	builder.addOrientating(OBJ_Player);
	builder.addAnimating(OBJ_Player);
	builder.addDotsEating();
	builder.addEnemyEating();

	player->setSpeed(80);
	player->setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Player, 45));
	player->setPen(QPen(Qt::transparent));
	player->reset();	
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
	auto *behavior{enemy->findBehavior(BT_Controlling)};
	auto *controller{static_cast<EnemyControlling *>(behavior)};
	auto *personality{Factory::createPersonality(json.value("personality").toInt())};
	auto *grid{Game::ref().level()->grid()};
	const auto &target{grid->mapFromGrid(Vector2(column, row))};

	personality->setScatterTarget(target);

	if (personality->type() == PT_Shying)
		static_cast<Shying *>(personality)->setPartner(Game::ref().level()->enemies().at(0));

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

	BehaviorBuilder builder;

	builder.setGameObject(enemy);
	builder.addColoring(color);
	builder.addSpawning(position);
	builder.addMoving(direction);
	builder.addControlling(OBJ_Enemy);
	builder.addOrientating(OBJ_Enemy);
	builder.addAnimating(OBJ_Enemy);
	builder.addKilling();

	enemy->setSpeed(75);
	enemy->setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Enemy, 0));
	enemy->setPen(QPen(Qt::transparent));

	Game::ref().level()->enemies().append(enemy);
	Game::ref().level()->addItem(enemy);

	enemy->reset();

	return enemy;
}

GameObject *Configurator::createEnergizer(const QPoint &cell)
{
	auto *energizer{new Energizer()};
	auto *grid{Game::ref().level()->grid()};

	BehaviorBuilder builder;

	builder.setGameObject(energizer);
	builder.addEnergizing();
	builder.addAnimating(OBJ_Energizer);

	energizer->setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Energizer, 8));
	energizer->setPen(QPen(Qt::transparent));
	energizer->setBrush(Game::ref().palette()->color(CR_Energizer));
	energizer->setPos(grid->mapFromGrid(cell.y(), cell.x()));

	return energizer;
}

GameObject *Configurator::createTeleporter(const QPointF &src, const QPointF &dst)
{
	auto *teleporter{new Teleporter()};

	BehaviorBuilder builder;

	builder.setGameObject(teleporter);
	builder.addTeleporting(dst);

	teleporter->setPos(src);
	teleporter->setPath(PathBuilder::teleporterPath());
	teleporter->setPen(QPen(Qt::transparent));
	teleporter->setBrush(Qt::transparent);
	teleporter->setFlag(QGraphicsItem::ItemHasNoContents);

	return teleporter;
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

int Configurator::key2role(const QString &key) const
{
	return QHash<QString, int>{{"Background", CR_Background},
							   {"Player", CR_Player},
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
