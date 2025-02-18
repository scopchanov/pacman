#include "CalmDownEnemies.h"
#include "engine/Game.h"
#include "engine/objects/Enemy.h"

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
	const QList<Enemy *> enemies{Game::ref().enemies()};

	for (auto *enemy : enemies)
		if (enemy->state() != Enemy::ST_Eaten)
			enemy->calmDown();
}
