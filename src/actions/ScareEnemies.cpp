#include "ScareEnemies.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "objects/Enemy.h"

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
	const QList<Enemy *> &enemies{Game::ref().level()->enemies()};

	for (auto *enemy : enemies)
		if (enemy->state() != Enemy::ST_Eaten)
			enemy->scare();
}
