#include "AbstractTimedBehavior.h"
#include "Game.h"

AbstractTimedBehavior::AbstractTimedBehavior(AbstractGameObject *parent) :
	AbstractBehavior(parent)
{

}

GameClock *AbstractTimedBehavior::clock() const
{
	return Game::ref().clock();
}
