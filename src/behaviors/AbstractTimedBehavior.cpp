#include "AbstractTimedBehavior.h"
#include "Game.h"

AbstractTimedBehavior::AbstractTimedBehavior(AbstractGameObject *parent) :
	AbstractBehavior(parent)
{

}

Clock *AbstractTimedBehavior::clock() const
{
	return Game::ref().clock();
}
