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
#include "engine/Tile.h"
#include "engine/Tilemap.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/EnemyAnimation.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/behaviors/EnemyOrientation.h"
#include "engine/behaviors/KillPlayer.h"
#include "engine/behaviors/PoweringUp.h"
#include "engine/behaviors/PowerUpAnimation.h"
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

	_game->_dotMatrix = json.value("dots").toArray();

	_game->_grid->setGridSize(rows, columns);
	_game->_grid->setCellSize(QSizeF(width, height));

	_game->walls()->setGrid(_game->_grid);
	_game->dots()->setGrid(_game->_grid);

	buildTilemap(_game->walls(), wallMatrix, QPen(QColor(0x1976D2), 4), QBrush(Qt::transparent));
	buildTilemap(_game->dots(), _game->_dotMatrix, QPen(Qt::transparent), QBrush(0x999999));

	_game->walls()->setTile(13, 14, createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), QBrush(Qt::transparent)));
	_game->walls()->setTile(13, 15, createTile(PathBuilder::TT_HLineLow, QPen(QColor(0xBA68C8), 6), QBrush(Qt::transparent)));

	_game->_pacman->setSpawnPosition({playerX, playerY});
	_game->_pacman->setup(_game);

	_game->_scene->addItem(_game->_pacman);
	_game->_scene->addItem(_game->_walls);
	_game->_scene->addItem(_game->_dots);

	createEnemies(enemies);
	_game->_scene->addItem(createPowerUp({2, 4}));
	_game->_scene->addItem(createPowerUp({27, 4}));
	_game->_scene->addItem(createPowerUp({2, 24}));
	_game->_scene->addItem(createPowerUp({27, 24}));

	_game->stateMachine()->setGameClock(_game->_clock);
	_game->_scene->addItem(createTeleporter(_game->_grid->cellPosition(15, 0), _game->_grid->cellPosition(15, 28)));
	_game->_scene->addItem(createTeleporter(_game->_grid->cellPosition(15, 29), _game->_grid->cellPosition(15, 2)));
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
			Tile *tile{element.isEmpty() ? nullptr
										 : createTile(element["index"].toInt(),
													  pen, brush)};

			tilemap->setTile(m, n, tile);
			n++;
		}

		m++;
	}
}

Tile *Configurator::createTile(int index, const QPen &pen, const QBrush &brush)
{
	auto *tile{new Tile()};

	tile->setPath(PathBuilder::tilePath(PathBuilder::TileType(index)));
	tile->setPen(pen);
	tile->setBrush(brush);

	return tile;
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

		personality->setScatterTarget(_game->_grid->cellPosition(Vector2(column, row)));
		personality->setPlayer(_game->_pacman);
		personality->setGrid(_game->_grid);

		if (personality->type() == AbstractPersonality::PT_Shying)
			static_cast<Shying *>(personality)->setPartner(_game->_ghosts.at(0));

		enemy->setPersonality(personality);

		_game->stateMachine()->addEnemyController(controller);
	}
}

Ghost *Configurator::createEnemy(const QPointF &position, const QColor &color, int direction)
{
	auto *ghost{new Ghost()};

	ghost->setSpawnPosition(position);

	auto *movement{new CharacterMovement(ghost)};
	auto *orientation{new EnemyOrientation(ghost)};
	auto *enemyController{new EnemyController(ghost)};
	auto *animation{new EnemyAnimation(ghost)};
	auto *killPlayer{new KillPlayer(ghost)};
	auto *eventPlayerDies{new GameEvent(_game)};

	enemyController->setCharacterMovement(movement);
	enemyController->setPlayer(_game->_pacman);
	enemyController->setGrid(_game->_grid);

	movement->setGameClock(_game->_clock);
	movement->setTilemap(_game->_walls);
	movement->setMovingSpeed(150);
	movement->setInitialDirection(dir2vec(direction));

	orientation->setMovement(movement);

	animation->setGameClock(_game->_clock);

	killPlayer->setGameClock(_game->_clock);
	killPlayer->setPlayer(_game->_pacman);
	killPlayer->setEventPlayerDies(eventPlayerDies);

	ghost->addBehavior(enemyController);
	ghost->addBehavior(movement);
	ghost->addBehavior(orientation);
	ghost->addBehavior(animation);
	ghost->addBehavior(killPlayer);

	ghost->setBrush(color);

	connect(eventPlayerDies, &GameEvent::triggered, _game, &Game::onPlayerDies);

	_game->_ghosts.append(ghost);
	_game->_scene->addItem(ghost);

	return ghost;
}

GameObject *Configurator::createPowerUp(const QPoint &cell)
{
	auto *powerUp{new GameObject()};
	auto *powering{new PoweringUp(powerUp)};
	auto *animation{new PowerUpAnimation(powerUp)};

	powering->setPlayer(_game->_pacman);

	for (auto *ghost : std::as_const(_game->_ghosts))
		powering->addEnemy(ghost);

	animation->setGameClock(_game->_clock);

	powerUp->setPos(_game->_grid->cellPosition(cell.y(), cell.x()));
	powerUp->setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_PowerUp, 16));
	powerUp->setPen(QPen(Qt::transparent));
	powerUp->setBrush(Qt::white);

	powerUp->addBehavior(powering);
	powerUp->addBehavior(animation);

	return powerUp;
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
