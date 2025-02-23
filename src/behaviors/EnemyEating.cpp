#include "EnemyEating.h"
#include "GameEvent.h"
#include "GameGlobals.h"
#include "objects/Enemy.h"
#include <QHash>

EnemyEating::EnemyEating(AbstractGameObject *parent) :
	AbstractBehavior(parent),
	_enemiesEaten{0},
	_eventEnemyEaten{nullptr}
{

}

void EnemyEating::setEvent(GameEvent *event)
{
	_eventEnemyEaten = event;
}

int EnemyEating::type() const
{
	return BT_EnemyEating;
}

void EnemyEating::reset()
{
	_enemiesEaten = 0;
}

void EnemyEating::performActions()
{
	if (!_eventEnemyEaten)
		return;

	const auto &collidingObjects{parent()->collidingObjects()};

	for (auto *gameObject : collidingObjects)
		if (gameObject->objectType() == OBJ_Enemy)
			eatEnemy(static_cast<Enemy *>(gameObject));
}

void EnemyEating::eatEnemy(Enemy *enemy)
{
	if (enemy->state() != Enemy::ST_Frightened)
		return;

	enemy->eat();

	_eventEnemyEaten->setProperty("points", points());
	_eventEnemyEaten->trigger();

	_enemiesEaten++;

	if (_enemiesEaten >= 4)
		_enemiesEaten = 0;
}

int EnemyEating::points() const
{
	return QHash<int, int>{{0, 20}, {1, 40}, {2, 80}, {3, 160}}.value(_enemiesEaten);
}
