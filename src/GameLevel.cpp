#include "GameLevel.h"
#include "Clock.h"
#include "LevelState.h"
#include "Tilemap.h"
#include "components/actions/DeleteGameObject.h"
#include "components/actions/control/ControlEnemy.h"
#include "components/behaviors/Delaying.h"
#include "objects/Enemy.h"
#include "objects/Fruit.h"
#include "objects/Player.h"
#include "objects/Deenergizer.h"

GameLevel::GameLevel(QObject *parent) :
	Scene{parent},
	_state{new LevelState(this)},
	_walls{new Tilemap()},
	_dots{new Tilemap()},
	_player{new Player()},
	_deenergizer{new Deenergizer()},
	_dotsEaten{0}
{
	addItem(_walls);
	addItem(_dots);
	addItem(_player);
	addItem(_deenergizer);

	connect(clock(), &Clock::tick, _state, &LevelState::advance);
}

Tilemap *GameLevel::walls() const
{
	return _walls;
}

Tilemap *GameLevel::dots() const
{
	return _dots;
}

Player *GameLevel::player() const
{
	return _player;
}

void GameLevel::addEnemy(Enemy *enemy)
{
	_enemies.append(enemy);

	addItem(enemy);
}

QList<Enemy *> GameLevel::enemies() const
{
	return _enemies;
}

LevelState *GameLevel::state() const
{
	return _state;
}

Deenergizer *GameLevel::deenergizer() const
{
	return _deenergizer;
}

void GameLevel::reset()
{
	Scene::reset();

	_state->reset();
	_deenergizer->deactivate();
}

void GameLevel::onDotEaten()
{
	_dotsEaten++;

	if (_dotsEaten == 70)
		createFruit();

	if (_dotsEaten == 170)
		createFruit();
}

void GameLevel::createFruit()
{
	auto *fruit{new Fruit()};
	auto *delaying{new Delaying()};
	auto *deleteGameObject{new DeleteGameObject(delaying)};

	deleteGameObject->setGameObject(fruit);

	delaying->addComponent(deleteGameObject);
	delaying->setDuration(9.5);

	fruit->addComponent(delaying);

	addItem(fruit);
}
