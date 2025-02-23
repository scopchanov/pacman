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

	auto *walls{level()->walls()};
	auto *dots{level()->dots()};

	configurePalette(json.value("palette").toObject());
	configureGrid(json.value("grid").toObject());

	walls->setGrid(grid());
	dots->setGrid(grid());

	buildTilemap(walls, json.value("walls").toArray(), QPen(palette()->color(CR_Wall), 4), QBrush(Qt::transparent));
	buildTilemap(dots, json.value("dots").toArray(), QPen(Qt::transparent), palette()->color(CR_Dot));

	walls->setTile(13, 14, createTile(PathBuilder::TT_HLineLow, QPen(palette()->color(CR_Door), 6), Qt::transparent));
	walls->setTile(13, 15, createTile(PathBuilder::TT_HLineLow, QPen(palette()->color(CR_Door), 6), Qt::transparent));

	configurePlayer(json.value("player").toObject());
	createEnergizers(json.value("energizers").toArray());
	createTeleporters(json.value("teleporters").toArray());
	createEnemies(json.value("enemies").toArray());
}

GamePalette *Configurator::palette() const
{
	return Game::ref().palette();
}

GameLevel *Configurator::level() const
{
	return Game::ref().level();
}

Grid *Configurator::grid() const
{
	return level()->grid();
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

void Configurator::configurePlayer(const QJsonObject &json)
{
	BehaviorBuilder builder;
	auto *player{level()->player()};
	qreal x{json.value("position").toObject().value("x").toDouble()};
	qreal y{json.value("position").toObject().value("y").toDouble()};

	builder.setGameObject(player);
	builder.addColoring(palette()->color(CR_Player));
	builder.addSpawning({x, y});

	auto *moving{new Moving(player)};
	moving->setTilemap(level()->walls());
	moving->setNextDirection(V2_LEFT);
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

void Configurator::createEnemies(const QJsonArray &enemies)
{
	for (const auto &enemy : enemies)
		createEnemy(enemy.toObject());
}

void Configurator::createEnemy(const QJsonObject &json)
{
	BehaviorBuilder builder;
	int role{key2role(json.value("name").toString())};
	const QColor &color{palette()->color(role)};
	const QJsonObject &position{json.value("position").toObject()};
	qreal posX{position.value("x").toDouble()};
	qreal posY{position.value("y").toDouble()};
	int direction{json.value("direction").toInt()};
	const QJsonObject &cell{json.value("scatterTargetCell").toObject()};
	int row{cell.value("row").toInt()};
	int column{cell.value("column").toInt()};
	auto *enemy{new Enemy()};
	auto *leftEye{new GhostEye(enemy)};
	auto *rightEye{new GhostEye(enemy)};

	leftEye->setPos(-6, -6);
	rightEye->setPos(6, -6);

	builder.setGameObject(enemy);
	builder.addColoring(color);
	builder.addSpawning({posX, posY});
	builder.addMoving(direction);
	builder.addControlling(OBJ_Enemy);
	builder.addOrientating(OBJ_Enemy);
	builder.addAnimating(OBJ_Enemy);
	builder.addKilling();

	enemy->setSpeed(75);
	enemy->setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Enemy, 0));
	enemy->setPen(QPen(Qt::transparent));

	level()->enemies().append(enemy);
	level()->addItem(enemy);

	auto *behavior{enemy->findBehavior(BT_Controlling)};
	auto *controller{static_cast<EnemyControlling *>(behavior)};
	auto *personality{Factory::createPersonality(json.value("personality").toInt())};
	const auto &target{grid()->mapFromGrid(Vector2(column, row))};

	personality->setScatterTarget(target);

	if (personality->type() == PT_Shying)
		static_cast<Shying *>(personality)->setPartner(level()->enemies().at(0));

	enemy->setPersonality(personality);

	Game::ref().stateMachine()->addEnemyController(controller);

	enemy->reset();
}

void Configurator::createEnergizers(const QJsonArray &energizers)
{
	for (const auto &energizer : energizers)
		createEnergizer(energizer.toObject());
}

void Configurator::createEnergizer(const QJsonObject &json)
{
	BehaviorBuilder builder;
	int column{json.value("column").toInt()};
	int row{json.value("row").toInt()};
	const QPoint &cell{column, row};
	auto *energizer{new Energizer()};

	builder.setGameObject(energizer);
	builder.addEnergizing();
	builder.addAnimating(OBJ_Energizer);

	energizer->setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Energizer, 8));
	energizer->setPen(QPen(Qt::transparent));
	energizer->setBrush(palette()->color(CR_Energizer));
	energizer->setPos(grid()->mapFromGrid(cell.y(), cell.x()));
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
	BehaviorBuilder builder;
	const QJsonObject &jsonSource{json.value("source").toObject()};
	const QJsonObject &jsonDestination{json.value("destination").toObject()};
	int srcRow{jsonSource.value("row").toInt()};
	int srcCol{jsonSource.value("column").toInt()};
	int dstRow{jsonDestination.value("row").toInt()};
	int dstCol{jsonDestination.value("column").toInt()};
	const QPointF &src{grid()->mapFromGrid(srcRow, srcCol).toPointF()};
	const QPointF &dst{grid()->mapFromGrid(dstRow, dstCol).toPointF()};
	auto *teleporter{new Teleporter()};

	builder.setGameObject(teleporter);
	builder.addTeleporting(dst);

	teleporter->setPos(src);
	teleporter->setPath(PathBuilder::teleporterPath());
	teleporter->setPen(QPen(Qt::transparent));
	teleporter->setBrush(Qt::transparent);
	teleporter->setFlag(QGraphicsItem::ItemHasNoContents);
	teleporter->reset();

	level()->addItem(teleporter);
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
