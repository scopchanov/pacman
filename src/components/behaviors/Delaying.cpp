#include "Delaying.h"
#include "Game.h"
#include "Clock.h"
#include "GameGlobals.h"
#include <QVariant>

Delaying::Delaying(AbstractComponent *parent) :
	AbstractBehavior(parent),
	_duration{0.0},
	_time{0.0}
{

}

qreal Delaying::duration() const
{
	return _duration;
}

void Delaying::setDuration(qreal duration)
{
	_duration = duration;
}

qreal Delaying::time() const
{
	return _time;
}

int Delaying::type() const
{
	return BT_Delaying;
}

void Delaying::reset()
{
	_time = 0.0;

	emitSignal();
}

void Delaying::performTasks()
{
	if (increaseTime() && delayDurationExceeded())
		AbstractBehavior::performTasks();
}

bool Delaying::increaseTime()
{
	if (delayDurationExceeded())
		return false;

	_time += Game::ref().clock()->deltaTime();

	emitSignal();

	return true;
}

void Delaying::emitSignal()
{
	emit progressChanged(_time/_duration);
}

bool Delaying::delayDurationExceeded() const
{
	return _time >= _duration;
}
