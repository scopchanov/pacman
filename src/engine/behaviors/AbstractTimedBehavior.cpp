#include "AbstractTimedBehavior.h"

AbstractTimedBehavior::AbstractTimedBehavior(GameObject *parent) :
	AbstractBehavior(parent),
	_clock{nullptr}
{

}

GameClock *AbstractTimedBehavior::clock() const
{
	return _clock;
}

void AbstractTimedBehavior::setClock(GameClock *clock)
{
	_clock = clock;
}

void AbstractTimedBehavior::performActions()
{
	if (!_clock)
		return;

	performTimedActions();
}
