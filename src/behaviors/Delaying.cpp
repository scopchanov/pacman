#include "Delaying.h"
#include "Clock.h"
#include "Event.h"
#include "GameGlobals.h"
#include "AbstractAction.h"
#include <QVariant>

Delaying::Delaying(AbstractComponent *parent) :
	AbstractTimedBehavior(parent),
	_duration{0.0},
	_time{0.0},
	_eventTick{nullptr}
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

void Delaying::setEventTick(Event *event)
{
	_eventTick = event;
}

int Delaying::type() const
{
	return BT_Delaying;
}

void Delaying::reset()
{
	_time = 0.0;
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

	_time += clock()->deltaTime();

	triggerTickEvent();

	return true;
}

void Delaying::triggerTickEvent()
{
	if (!_eventTick)
		return;

	_eventTick->setProperty("time", _time);
	_eventTick->trigger();
}

bool Delaying::delayDurationExceeded() const
{
	return _time >= _duration;
}
