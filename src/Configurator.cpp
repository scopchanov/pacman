#include "Configurator.h"
#include "PathBuilder.h"
#include "engine/AiStateMachine.h"
#include "engine/Game.h"
#include "engine/GameEvent.h"
#include "engine/GameScene.h"
#include "engine/GameClock.h"
#include "engine/Ghost.h"
#include "engine/Grid.h"
#include "engine/Pacman.h"
#include "engine/Teleporter.h"
#include "engine/Tilemap.h"
#include "engine/actions/EnergizePlayer.h"
#include "engine/actions/FrightenEnemies.h"
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
	QObject{parent},
	_game{nullptr}
{

}

Game *Configurator::game() const
{
	return _game;
}

void Configurator::setGame(Game *game)
{
	_game = game;
}

void Configurator::configure(const QJsonObject &json)
{
	if (!_game || json.isEmpty())
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

	_game->stateMachine()->setGameClock(_game->_clock);

	_game->_dotMatrix = json.value("dots").toArray();

	_game->_grid->setGridSize(rows, columns);
	_game->_grid->setCellSize(QSizeF(width, height));

	_game->walls()->setGrid(_game->_grid);
	_game->dots()->setGrid(_game->_grid);

	_game->buildTilemap(_game->walls(), wallMatrix, QPen(QColor(0x1976D2), 4), QBrush(Qt::transparent));
	_game->buildTilemap(_game->dots(), _game->_dotMatrix, QPen(Qt::transparent), QBrush(0x999999));

	_game->walls()->setTile(13, 14, _game->createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), Qt::transparent));
	_game->walls()->setTile(13, 15, _game->createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), Qt::transparent));

	_game->_pacman->setSpawnPosition({playerX, playerY});
	_game->_pacman->setup(_game);

	_game->_scene->addItem(createEnergizer({2, 4}));
	_game->_scene->addItem(createEnergizer({27, 4}));
	_game->_scene->addItem(createEnergizer({2, 24}));
	_game->_scene->addItem(createEnergizer({27, 24}));
	_game->_scene->addItem(_game->_pacman);
	_game->_scene->addItem(_game->_walls);
	_game->_scene->addItem(_game->_dots);
	_game->_scene->addItem(createTeleporter(_game->_grid->mapFromGrid(15, 0),
											_game->_grid->mapFromGrid(15, 28)));
	_game->_scene->addItem(createTeleporter(_game->_grid->mapFromGrid(15, 29),
											_game->_grid->mapFromGrid(15, 2)));

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

		personality->setScatterTarget(_game->_grid->mapFromGrid(Vector2(column, row)));
		personality->setPlayer(_game->_pacman);
		personality->setGrid(_game->_grid);

		if (personality->type() == AbstractPersonality::PT_Shying)
			static_cast<Shying *>(personality)->setPartner(_game->_enemies.at(0));

		enemy->setPersonality(personality);

		_game->stateMachine()->addEnemyController(controller);
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
	auto *eventPlayerDies{new GameEvent(_game)};

	coloring->setColor(color);

	enemyController->setCharacterMovement(movement);
	enemyController->setPlayer(_game->_pacman);
	enemyController->setGrid(_game->_grid);

	movement->setClock(_game->_clock);
	movement->setTilemap(_game->_walls);
	movement->setSpeed(170.4545465625);
	movement->setInitialDirection(dir2vec(direction));

	orientation->setMovement(movement);

	animation->setClock(_game->_clock);

	killPlayer->setClock(_game->_clock);
	killPlayer->setPlayer(_game->_pacman);
	killPlayer->setEventPlayerDies(eventPlayerDies);

	ghost->addBehavior(coloring);
	ghost->addBehavior(enemyController);
	ghost->addBehavior(movement);
	ghost->addBehavior(orientation);
	ghost->addBehavior(animation);
	ghost->addBehavior(killPlayer);

	ghost->setBrush(color);

	connect(eventPlayerDies, &GameEvent::triggered, _game, &Game::onPlayerDies);

	_game->_enemies.append(ghost);
	_game->_scene->addItem(ghost);

	return ghost;
}

GameObject *Configurator::createEnergizer(const QPoint &cell)
{
	auto *energizer{new GameObject()};
	auto *energizing{new Energizing(energizer)};
	auto *animation{new EnergizerAnimation(energizer)};
	auto *actEnergizePlayer{new EnergizePlayer(energizing)};
	auto *actFrightenGhosts{new FrightenEnemies(energizing)};
	auto *eventPlayerEnergized{new GameEvent(_game)};

	energizing->setPlayer(_game->_pacman);

	for (auto *ghost : std::as_const(_game->_enemies))
		energizing->addEnemy(ghost);

	actEnergizePlayer->setGame(_game);
	actFrightenGhosts->setGame(_game);

	energizing->addAction(actEnergizePlayer);
	energizing->addAction(actFrightenGhosts);
	energizing->setEvent(eventPlayerEnergized);

	animation->setClock(_game->_clock);

	energizer->setPos(_game->_grid->mapFromGrid(cell.y(), cell.x()));
	energizer->setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Energizer, 16));
	energizer->setPen(QPen(Qt::transparent));
	energizer->setBrush(Qt::white);

	energizer->addBehavior(energizing);
	energizer->addBehavior(animation);

	connect(eventPlayerEnergized, &GameEvent::triggered,
			_game, &Game::onPlayerEnergized);

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
