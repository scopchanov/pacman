#include "AbstractTimedBehavior.h"
#include "engine/Game.h"

AbstractTimedBehavior::AbstractTimedBehavior(GameObject *parent) :
	AbstractBehavior(parent)
{

}

GameClock *AbstractTimedBehavior::clock() const
{
	return Game::ref().clock();
}
