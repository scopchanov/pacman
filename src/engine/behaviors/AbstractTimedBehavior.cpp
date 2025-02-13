#include "AbstractTimedBehavior.h"

AbstractTimedBehavior::AbstractTimedBehavior(GameObject *parent) :
	AbstractBehavior(parent),
	_gameTimer{nullptr}
{

}

GameClock *AbstractTimedBehavior::gameClock() const
{
	return _gameTimer;
}

void AbstractTimedBehavior::setGameClock(GameClock *gameTimer)
{
	_gameTimer = gameTimer;
}

void AbstractTimedBehavior::performActions()
{
	if (!_gameTimer)
		return;

	performTimedActions();
}
