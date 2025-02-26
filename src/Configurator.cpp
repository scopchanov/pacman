#include "Configurator.h"
#include "Factory.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "Palette.h"
#include "Grid.h"
#include "PathBuilder.h"
#include "Tilemap.h"
#include "ComponentBuilder.h"
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

	configurePalette(json.value("palette").toObject());
	configureGrid(json.value("grid").toObject());
	configureWalls(json.value("walls").toArray());
	configureDots(json.value("dots").toArray());
	configurePlayer(json.value("player").toObject());
	createDoors(json.value("doors").toArray());
	createEnergizers(json.value("energizers").toArray());
	createTeleporters(json.value("teleporters").toArray());
	createEnemies(json.value("enemies").toArray());
}

void Configurator::configurePalette(const QJsonObject &json)
{
	const auto &keys{json.keys()};

	for (const auto &key : keys) {
		const QColor &color{json.value(key).toString()};

		palette()->setColor(key2role(key), color);
	}
}

void Configurator::configureGrid(const QJsonObject &json)
{
	const QJsonObject &cell{json.value("cell").toObject()};
	int rows{json.value("rows").toInt()};
	int columns{json.value("columns").toInt()};
	qreal width{cell.value("width").toDouble()};
	qreal height{cell.value("height").toDouble()};

	grid()->setGridSize(rows, columns);
	grid()->setCellSize(QSizeF(width, height));
}

void Configurator::configureWalls(const QJsonArray &jsonWalls)
{
	// TODO: Improve me

	auto *walls{level()->walls()};

	walls->setGrid(grid());
	buildTilemap(walls, jsonWalls, QPen(palette()->color(CR_Wall), 4),
				 QBrush(Qt::transparent));
}

void Configurator::configureDots(const QJsonArray &jsonDots)
{
	// TODO: Improve me

	auto *dots{level()->dots()};

	dots->setGrid(grid());
	buildTilemap(dots, jsonDots, QPen(Qt::transparent), palette()->color(CR_Dot));
}

void Configurator::configurePlayer(const QJsonObject &json)
{
	ComponentBuilder builder;
	const QJsonObject &position{json.value("position").toObject()};
	qreal x{position.value("x").toDouble()};
	qreal y{position.value("y").toDouble()};
	auto *player{level()->player()};

	builder.setGameObject(player);
	builder.addColoring(palette()->color(CR_Player));
	builder.addSpawning({x, y});
	builder.addMoving(0);
	builder.addControlling(OBJ_Player);
	builder.addOrientating(OBJ_Player);
	builder.addAnimating(OBJ_Player);
	builder.addDotsEating();
	builder.addEnemyEating();

	player->setSpeed(80);
	player->setPen(QPen(Qt::transparent));
	player->reset();
}

void Configurator::createEnemies(const QJsonArray &enemies)
{
	for (const auto &enemy : enemies)
		createEnemy(enemy.toObject());
}

void Configurator::createEnemy(const QJsonObject &json)
{
	ComponentBuilder builder;
	const QJsonObject &position{json.value("position").toObject()};
	const QJsonObject &personality{json.value("personality").toObject()};
	int role{key2role(json.value("name").toString())};
	qreal x{position.value("x").toDouble()};
	qreal y{position.value("y").toDouble()};
	auto *enemy{new Enemy()};

	createEye(enemy, {-6, -6});
	createEye(enemy, {6, -6});

	builder.setGameObject(enemy);
	builder.addColoring(palette()->color(role));
	builder.addSpawning({x, y});
	builder.addMoving(json.value("direction").toInt());
	builder.addControlling(OBJ_Enemy);
	builder.addOrientating(OBJ_Enemy);
	builder.addAnimating(OBJ_Enemy);
	builder.addKilling();

	enemy->setPersonality(createPersonality(personality));
	enemy->setPen(QPen(Qt::transparent));
	enemy->setSpeed(75);
	enemy->reset();

	level()->addEnemy(enemy);
}

AbstractPersonality *Configurator::createPersonality(const QJsonObject &json)
{
	const QJsonObject &cell{json.value("scatterTargetCell").toObject()};
	int row{cell.value("row").toInt()};
	int column{cell.value("column").toInt()};
	auto *personality{Factory::createPersonality(json.value("type").toInt())};

	personality->setScatterTarget(gridPosition(row, column));

	if (personality->type() == PT_Shying)
		static_cast<Shying *>(personality)->setPartner(level()->enemies().at(0));

	return personality;
}

void Configurator::createEye(AbstractGameObject *gameObject, const QPointF &position)
{
	auto *eye{new GhostEye(gameObject)};

	eye->setPos(position);
}

void Configurator::createDoors(const QJsonArray &doors)
{
	for (const auto &door : doors)
		createDoor(door.toObject());
}

void Configurator::createDoor(const QJsonObject &json)
{
	const QPen &pen{palette()->color(CR_Door), 6, Qt::SolidLine, Qt::RoundCap};
	auto *door{createTile(PathBuilder::TT_Door, pen, Qt::transparent)};
	auto *walls{level()->walls()};
	int row{json.value("row").toInt()};
	int column{json.value("column").toInt()};

	walls->setTile(row, column, door);
}

void Configurator::createEnergizers(const QJsonArray &energizers)
{
	for (const auto &energizer : energizers)
		createEnergizer(energizer.toObject());
}

void Configurator::createEnergizer(const QJsonObject &json)
{
	ComponentBuilder builder;
	int column{json.value("column").toInt()};
	int row{json.value("row").toInt()};
	auto *energizer{new Energizer()};

	builder.setGameObject(energizer);
	builder.addEnergizing();
	builder.addAnimating(OBJ_Energizer);

	energizer->setPen(QPen(Qt::transparent));
	energizer->setBrush(palette()->color(CR_Energizer));
	energizer->setPos(gridPosition(row, column));
	energizer->reset();

	level()->addItem(energizer);
}

void Configurator::createTeleporters(const QJsonArray &teleporters)
{
	for (const auto &teleporter : teleporters)
		createTeleporter(teleporter.toObject());
}

void Configurator::createTeleporter(const QJsonObject &json)
{
	ComponentBuilder builder;
	const QJsonObject &jsonSource{json.value("source").toObject()};
	const QJsonObject &jsonDestination{json.value("destination").toObject()};
	int srcRow{jsonSource.value("row").toInt()};
	int srcCol{jsonSource.value("column").toInt()};
	int dstRow{jsonDestination.value("row").toInt()};
	int dstCol{jsonDestination.value("column").toInt()};
	const QPointF &src{gridPosition(srcRow, srcCol)};
	const QPointF &dst{gridPosition(dstRow, dstCol)};
	auto *teleporter{new Teleporter()};

	builder.setGameObject(teleporter);
	builder.addAnimating(OBJ_Teleporter);
	builder.addTeleporting(dst);

	teleporter->setPos(src);
	teleporter->setPen(QPen(Qt::transparent));
	teleporter->setBrush(palette()->color(CR_Teleporter));
	teleporter->reset();

	level()->addItem(teleporter);
}

void Configurator::buildTilemap(Tilemap *tilemap, const QJsonArray &matrix,
								const QPen &pen, const QBrush &brush)
{
	// TODO: Improve me

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
							   {"Energizer", CR_Energizer},
							   {"Teleporter", CR_Teleporter}}.value(key);
}

QPointF Configurator::gridPosition(int row, int column) const
{
	return grid()->mapFromGrid(row, column);
}

GameLevel *Configurator::level() const
{
	return Game::ref().level();
}

Palette *Configurator::palette() const
{
	return level()->palette();
}

Grid *Configurator::grid() const
{
	return level()->grid();
}
