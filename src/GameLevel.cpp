#include "GameLevel.h"
#include "Clock.h"
#include "Tilemap.h"
#include "components/actions/control/ControlEnemy.h"
#include "objects/Enemy.h"
#include "objects/LevelMode.h"
#include "objects/Player.h"
#include "objects/Deenergizer.h"

GameLevel::GameLevel(QObject *parent) :
	Scene{parent},
	_walls{new Tilemap()},
	_dots{new Tilemap()},
	_player{new Player()},
	_mode{new LevelMode()},
	_deenergizer{new Deenergizer()}
{
	addItem(_walls);
	addItem(_dots);
	addItem(_player);
	addItem(_deenergizer);
	addItem(_mode);

	// connect(clock(), &Clock::tick, _stateMachine, &AiStateMachine::advance);
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
	// auto *component{enemy->findComponent(ACT_Control)};
	// auto *controller{static_cast<ControlEnemy *>(component)};

	// _stateMachine->addEnemyController(controller);
	_enemies.append(enemy);

	addItem(enemy);
}

QList<Enemy *> GameLevel::enemies() const
{
	return _enemies;
}

LevelMode *GameLevel::mode() const
{
	return _mode;
}

Deenergizer *GameLevel::deenergizer() const
{
	return _deenergizer;
}

void GameLevel::reset()
{
	Scene::reset();

	// _state->reset();
	_deenergizer->deactivate();
}
