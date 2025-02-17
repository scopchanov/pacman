#include "ScareEnemies.h"
#include "engine/Game.h"
#include "engine/Enemy.h"

ScareEnemies::ScareEnemies(AbstractBehavior *parent) :
	AbstractAction{parent}
{

}

int ScareEnemies::type() const
{
	return ACT_ScareEnemies;
}

void ScareEnemies::performTask()
{
	const QList<Enemy *> enemies{Game::ref().enemies()};

	for (auto *enemy : enemies)
		if (enemy->state() != Enemy::ST_Eaten)
			enemy->scare();
}
