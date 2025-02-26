#include "AbstractTimedBehavior.h"
#include "Game.h"

AbstractTimedBehavior::AbstractTimedBehavior(AbstractComponent *parent) :
	AbstractBehavior(parent)
{

}

Clock *AbstractTimedBehavior::clock() const
{
	return Game::ref().clock();
}
