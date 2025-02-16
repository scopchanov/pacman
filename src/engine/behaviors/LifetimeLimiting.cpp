#include "LifetimeLimiting.h"
#include "engine/GameClock.h"
#include "engine/GameObject.h"

LifetimeLimiting::LifetimeLimiting(GameObject *parent) :
	AbstractTimedBehavior(parent),
	_duration{0.0},
	_time{0.0}
{

}

qreal LifetimeLimiting::duration() const
{
	return _duration;
}

void LifetimeLimiting::setDuration(qreal duration)
{
	_duration = duration;
}

int LifetimeLimiting::type() const
{
	return BT_LifetimeLimiting;
}

void LifetimeLimiting::reset()
{
	deleteGameObject();
}

void LifetimeLimiting::performTimedActions()
{
	_time += gameClock()->deltaTime();

	if (_time < _duration)
		return;

	deleteGameObject();
}

void LifetimeLimiting::deleteGameObject()
{
	parent()->deleteLater();
}
