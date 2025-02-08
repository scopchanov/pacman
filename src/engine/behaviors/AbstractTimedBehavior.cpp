#include "AbstractTimedBehavior.h"

AbstractTimedBehavior::AbstractTimedBehavior(GameObject *parent) :
	AbstractBehavior(parent),
	_gameTimer{nullptr}
{

}

GameTimer *AbstractTimedBehavior::gameTimer() const
{
	return _gameTimer;
}

void AbstractTimedBehavior::setGameTimer(GameTimer *gameTimer)
{
	_gameTimer = gameTimer;
}

void AbstractTimedBehavior::performActions()
{
	if (!_gameTimer)
		return;

	performTimedActions();
}
