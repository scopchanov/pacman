#include "CalmDownEnemies.h"
#include "Game.h"
#include "GameGlobals.h"
#include "objects/Enemy.h"

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
