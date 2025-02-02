#include "AbstractTimedBehavior.h"

AbstractTimedBehavior::AbstractTimedBehavior(GameObject *parent) :
	AbstractBehavior(parent),
	m_gameTimer{nullptr}
{

}

GameTimer *AbstractTimedBehavior::gameTimer() const
{
	return m_gameTimer;
}

void AbstractTimedBehavior::setGameTimer(GameTimer *gameTimer)
{
	m_gameTimer = gameTimer;
}

void AbstractTimedBehavior::performActions()
{
	if (!m_gameTimer)
		return;

	performTimedActions();
}
