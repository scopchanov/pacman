#include "EatEnemy.h"
#include "AbstractGameObject.h"
#include "GameGlobals.h"
#include "objects/Enemy.h"

EatEnemy::EatEnemy(AbstractComponent *parent) :
	AbstractAction(parent),
	_enemiesEaten{0}
{

}

int EatEnemy::type() const
{
	return ACT_EatEnemy;
}

void EatEnemy::reset()
{
	_enemiesEaten = 0;
}

void EatEnemy::performTasks()
{
	const auto &collidingObjects{gameObject()->collidingObjects()};

	for (auto *object : collidingObjects)
		if (object->objectType() == OBJ_Enemy)
			eatEnemy(static_cast<Enemy *>(object));
}

void EatEnemy::eatEnemy(Enemy *enemy)
{
	if (enemy->state() != Enemy::ST_Frightened)
		return;

	_enemiesEaten++;

	enemy->eat();

	setProperty("points", points());

	emit enemyEaten(enemy->pos());
}

int EatEnemy::points() const
{
	return 10*pow(2, _enemiesEaten);
}
