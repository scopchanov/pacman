#include "ScareEnemies.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "objects/Enemy.h"

ScareEnemies::ScareEnemies(AbstractComponent *parent) :
	AbstractAction{parent}
{

}

int ScareEnemies::type() const
{
	return ACT_ScareEnemies;
}

void ScareEnemies::performTasks()
{

}
