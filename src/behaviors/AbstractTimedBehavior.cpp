#include "AbstractTimedBehavior.h"
#include "Game.h"

AbstractTimedBehavior::AbstractTimedBehavior(GameObject *parent) :
	AbstractBehavior(parent)
{

}

GameClock *AbstractTimedBehavior::clock() const
{
	return Game::ref().clock();
}
