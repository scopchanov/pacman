#include "CalmDownEnemies.h"
#include "engine/Game.h"
#include "engine/Enemy.h"

CalmDownEnemies::CalmDownEnemies(AbstractBehavior *parent) :
	AbstractAction{parent}
{

}

int CalmDownEnemies::type() const
{
	return ACT_CalmDownEnemies;
}

void CalmDownEnemies::performTask()
{
	const QList<Enemy *> enemies{game()->enemies()};

	for (auto *enemy : enemies)
		if (enemy->state() != Enemy::ST_Eaten)
			enemy->calmDown();
}
