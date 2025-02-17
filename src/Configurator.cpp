#include "Configurator.h"
#include "PathBuilder.h"
#include "engine/AiStateMachine.h"
#include "engine/Game.h"
#include "engine/GameEvent.h"
#include "engine/GameScene.h"
#include "engine/GameClock.h"
#include "engine/Ghost.h"
#include "engine/Grid.h"
#include "engine/Player.h"
#include "engine/Teleporter.h"
#include "engine/Tilemap.h"
#include "engine/actions/DeleteGameObject.h"
#include "engine/actions/EnergizePlayer.h"
#include "engine/actions/ScareEnemies.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/Coloring.h"
#include "engine/behaviors/EnemyAnimation.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/behaviors/EnemyOrientation.h"
#include "engine/behaviors/KillPlayer.h"
#include "engine/behaviors/Energizing.h"
#include "engine/behaviors/EnergizerAnimation.h"
#include "engine/personalities/Shadowing.h"
#include "engine/personalities/Speeding.h"
#include "engine/personalities/Shying.h"
#include "engine/personalities/Poking.h"
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

	const QJsonArray &wallMatrix{json.value("walls").toArray()};
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
	const Game &game{Game::ref()};

	game.stateMachine()->setGameClock(game._clock);

	Game::ref()._dotMatrix = json.value("dots").toArray();

	game._grid->setGridSize(rows, columns);
	game._grid->setCellSize(QSizeF(width, height));

	game.walls()->setGrid(game._grid);
	game.dots()->setGrid(game._grid);

	Game::ref().buildTilemap(game.walls(), wallMatrix, QPen(QColor(0x1976D2), 4), QBrush(Qt::transparent));
	Game::ref().buildTilemap(game.dots(), game._dotMatrix, QPen(Qt::transparent), QBrush(0x999999));

	game.walls()->setTile(13, 14, Game::ref().createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), Qt::transparent));
	game.walls()->setTile(13, 15, Game::ref().createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), Qt::transparent));

	game._player->setSpawnPosition({playerX, playerY});
	game._player->setup();

	game._scene->addItem(createEnergizer({2, 4}));
	game._scene->addItem(createEnergizer({27, 4}));
	game._scene->addItem(createEnergizer({2, 24}));
	game._scene->addItem(createEnergizer({27, 24}));
	game._scene->addItem(game._player);
	game._scene->addItem(game._walls);
	game._scene->addItem(game._dots);
	game._scene->addItem(createTeleporter(game._grid->mapFromGrid(15, 0),
											game._grid->mapFromGrid(15, 28)));
	game._scene->addItem(createTeleporter(game._grid->mapFromGrid(15, 29),
											game._grid->mapFromGrid(15, 2)));

	createEnemies(enemies);	
}

void Configurator::createEnemies(const QJsonArray &enemies)
{
	for (const auto &record : enemies) {
		const QJsonObject &json{record.toObject()};
		const QString &color{json.value("color").toString()};
		const QJsonObject &position{json.value("position").toObject()};
		qreal posX{position.value("x").toDouble()};
		qreal posY{position.value("y").toDouble()};
		int direction{json.value("direction").toInt()};
		const QJsonObject &cell{json.value("scatterTargetCell").toObject()};
		int row{cell.value("row").toInt()};
		int column{cell.value("column").toInt()};
		auto *enemy{createEnemy({posX, posY}, color, direction)};
		auto *behavior{enemy->findBehavior(AbstractBehavior::BT_EnemyController)};
		auto *controller{static_cast<EnemyController *>(behavior)};
		auto *personality{createPersonality(json.value("personality").toInt())};

		personality->setScatterTarget(Game::ref()._grid->mapFromGrid(Vector2(column, row)));
		personality->setPlayer(Game::ref()._player);
		personality->setGrid(Game::ref()._grid);

		if (personality->type() == AbstractPersonality::PT_Shying)
			static_cast<Shying *>(personality)->setPartner(Game::ref()._enemies.at(0));

		enemy->setPersonality(personality);

		Game::ref().stateMachine()->addEnemyController(controller);
	}
}

Ghost *Configurator::createEnemy(const QPointF &position, const QColor &color, int direction)
{
	auto *ghost{new Ghost()};

	ghost->setSpawnPosition(position);

	auto *coloring{new Coloring(ghost)};
	auto *movement{new CharacterMovement(ghost)};
	auto *orientation{new EnemyOrientation(ghost)};
	auto *enemyController{new EnemyController(ghost)};
	auto *animation{new EnemyAnimation(ghost)};
	auto *killPlayer{new KillPlayer(ghost)};
	auto *eventPlayerDies{new GameEvent()};

	coloring->setColor(color);

	enemyController->setCharacterMovement(movement);
	enemyController->setGrid(Game::ref()._grid);

	movement->setTilemap(Game::ref()._walls);
	movement->setSpeed(170.4545465625);
	movement->setInitialDirection(dir2vec(direction));

	orientation->setMovement(movement);

	killPlayer->setEventPlayerDies(eventPlayerDies);

	ghost->addBehavior(coloring);
	ghost->addBehavior(enemyController);
	ghost->addBehavior(movement);
	ghost->addBehavior(orientation);
	ghost->addBehavior(animation);
	ghost->addBehavior(killPlayer);

	ghost->setBrush(color);

	connect(eventPlayerDies, &GameEvent::triggered, &Game::ref(), &Game::onPlayerDies);

	Game::ref()._enemies.append(ghost);
	Game::ref()._scene->addItem(ghost);

	return ghost;
}

GameObject *Configurator::createEnergizer(const QPoint &cell)
{
	auto *energizer{new GameObject()};
	auto *energizing{new Energizing(energizer)};
	auto *animation{new EnergizerAnimation(energizer)};
	auto *actEnergizePlayer{new EnergizePlayer(energizing)};
	auto *actFrightenGhosts{new ScareEnemies(energizing)};
	auto *eventPlayerEnergized{new GameEvent()};

	energizing->setEvent(eventPlayerEnergized);
	energizing->setPlayer(Game().ref()._player);
	energizing->addAction(actEnergizePlayer);
	energizing->addAction(actFrightenGhosts);

	energizer->setPos(Game().ref()._grid->mapFromGrid(cell.y(), cell.x()));
	energizer->setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Energizer, 16));
	energizer->setPen(QPen(Qt::transparent));
	energizer->setBrush(Qt::white);

	energizer->addBehavior(energizing);
	energizer->addBehavior(animation);

	connect(eventPlayerEnergized, &GameEvent::triggered,
			&Game::ref(), &Game::onPlayerEnergized);

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

Vector2 Configurator::dir2vec(int direction)
{
	return QHash<int, Vector2>{{0, V2_LEFT}, {1, V2_UP}, {2, V2_RIGHT},
							   {3, V2_DOWN}}.value(direction);
}
