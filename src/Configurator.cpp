#include "Configurator.h"
#include "Factory.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "Grid.h"
#include "LevelState.h"
#include "Palette.h"
#include "Tilemap.h"
#include "builders/ObjectBuilder.h"
#include "builders/PathBuilder.h"
#include "builders/TilemapBuilder.h"
#include "components/actions/CalmDownEnemies.h"
#include "components/actions/DeactivateDeenergizer.h"
#include "components/actions/DeenergizePlayer.h"
#include "components/actions/control/ControlEnemy.h"
#include "components/actions/tilemap/Move.h"
#include "components/behaviors/Delaying.h"
#include "objects/Deenergizer.h"
#include "objects/Enemy.h"
#include "objects/Energizer.h"
#include "objects/EnemyEye.h"
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

	configureLevelState(json.value("stepDurations").toArray());
	configurePalette(json.value("palette").toObject());
	configureGrid(json.value("grid").toObject());
	configureWalls(json.value("walls").toArray());
	configureDots(json.value("dots").toArray());
	configureDeenergizer(json.value("deenergizer").toObject());
	configurePlayer(json.value("player").toObject());
	createDoors(json.value("doors").toArray());
	createEnergizers(json.value("energizers").toArray());
	createTeleporters(json.value("teleporters").toArray());
	createEnemies(json.value("enemies").toArray());
}

void Configurator::configureLevelState(const QJsonArray &jsonStepDurations)
{
	int step{0};

	for (auto const &duration : jsonStepDurations) {
		level()->state()->setStepDuration(step, duration.toDouble());
		step++;
	}
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
	TilemapBuilder builder;

	builder.setGrid(grid());
	builder.setTilemap(level()->walls());
	builder.setPen(QPen(palette()->color(CR_Wall), 4));
	builder.setBrush(Qt::transparent);

	builder.build(jsonWalls);
}

void Configurator::configureDots(const QJsonArray &jsonDots)
{
	TilemapBuilder builder;

	builder.setGrid(grid());
	builder.setTilemap(level()->dots());
	builder.setPen(QPen(Qt::transparent));
	builder.setBrush(palette()->color(CR_Dot));

	builder.build(jsonDots);
}

void Configurator::configureDeenergizer(const QJsonObject &json)
{
	auto *delaying{new Delaying()};
	auto *deenergizePlayer{new DeenergizePlayer(delaying)};
	auto *calmDownEnemies{new CalmDownEnemies(delaying)};
	auto *deactivateDeenergizer{new DeactivateDeenergizer(delaying)};
	auto *deenergizer{level()->deenergizer()};

	delaying->setDuration(json.value("duration").toDouble());
	delaying->addComponent(deenergizePlayer);
	delaying->addComponent(calmDownEnemies);
	delaying->addComponent(deactivateDeenergizer);
	delaying->setEnabled(false);

	connect(delaying, &Delaying::progressChanged,
			level(), &GameLevel::energizedProgressChanged);

	deenergizer->addComponent(delaying);
	deenergizer->setFlags(QGraphicsItem::ItemHasNoContents);
	deenergizer->reset();
}

void Configurator::configurePlayer(const QJsonObject &json)
{
	ObjectBuilder builder;
	const QJsonObject &position{json.value("position").toObject()};
	qreal x{position.value("x").toDouble()};
	qreal y{position.value("y").toDouble()};
	auto *player{level()->player()};

	builder.setGameObject(player);
	builder.addSpawn({x, y});
	builder.addMove(0);
	builder.addControl(OBJ_Player);
	builder.addOrientate(OBJ_Player, static_cast<Move *>(player->findComponent(ACT_Move)));
	builder.addAnimate(OBJ_Player);
	builder.addEatDot();
	builder.addEatEnemy();
	builder.addEatFruit();

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
	ObjectBuilder builder;
	const QJsonObject &position{json.value("position").toObject()};
	const QJsonObject &personality{json.value("personality").toObject()};
	qreal x{position.value("x").toDouble()};
	qreal y{position.value("y").toDouble()};
	auto *enemy{new Enemy()};

	builder.setGameObject(enemy);
	builder.addSpawn({x, y});
	builder.addMove(json.value("direction").toInt());
	builder.addControl(OBJ_Enemy);
	builder.addAnimate(OBJ_Enemy);
	builder.addKillPlayer();

	createEye(enemy, {-6, -6});
	createEye(enemy, {6, -6});

	enemy->setPersonality(createPersonality(personality));
	enemy->setPen(QPen(Qt::transparent));
	enemy->setSpeed(75);
	enemy->reset();

	level()->addEnemy(enemy);
}

void Configurator::createEye(AbstractGameObject *parent, const QPointF &pos)
{
	ObjectBuilder builder;
	auto *eye{new EnemyEye(parent)};
	auto *move{static_cast<Move *>(parent->findComponent(ACT_Move))};

	builder.setGameObject(eye);
	builder.addOrientate(OBJ_Enemy, move);

	eye->setPos(pos);
	eye->reset();
}

AbstractPersonality *Configurator::createPersonality(const QJsonObject &json)
{
	const QJsonObject &cell{json.value("scatterTargetCell").toObject()};
	int row{cell.value("row").toInt()};
	int column{cell.value("column").toInt()};
	auto *personality{Factory::createPersonality(json.value("type").toInt())};

	personality->setColorRole(json.value("colorRole").toInt());
	personality->setScatterTarget(gridPosition(row, column));

	if (personality->type() == PT_Shying)
		static_cast<Shying *>(personality)->setPartner(level()->enemies().at(0));

	return personality;
}

void Configurator::createDoors(const QJsonArray &doors)
{
	for (const auto &door : doors)
		createDoor(door.toObject());
}

void Configurator::createDoor(const QJsonObject &json)
{
	TilemapBuilder builder;
	int row{json.value("row").toInt()};
	int column{json.value("column").toInt()};
	const QColor &color{palette()->color(CR_Door)};

	builder.setTilemap(level()->walls());
	builder.setPen(QPen(color, 6, Qt::SolidLine, Qt::RoundCap));
	builder.setBrush(Qt::transparent);
	builder.setTile(row, column, PathBuilder::TT_Door);
}

void Configurator::createEnergizers(const QJsonArray &energizers)
{
	for (const auto &energizer : energizers)
		createEnergizer(energizer.toObject());
}

void Configurator::createEnergizer(const QJsonObject &json)
{
	ObjectBuilder builder;
	int column{json.value("column").toInt()};
	int row{json.value("row").toInt()};
	auto *energizer{new Energizer()};

	builder.setGameObject(energizer);
	builder.addEnergizePlayer();
	builder.addAnimate(OBJ_Energizer);

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
	ObjectBuilder builder;
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
	builder.addAnimate(OBJ_Teleporter);
	builder.addTeleport(dst);

	teleporter->setPos(src);
	teleporter->setPen(QPen(Qt::transparent));
	teleporter->setBrush(palette()->color(CR_Teleporter));
	teleporter->reset();

	level()->addItem(teleporter);
}

int Configurator::key2role(const QString &key) const
{
	return QHash<QString, int>{{"Background", CR_Background},
							   {"Player", CR_Player},
							   {"PlayerEnergized", CR_PlayerEnergized},
							   {"Blinky", CR_Blinky},
							   {"Pinky", CR_Pinky},
							   {"Inky", CR_Inky},
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
