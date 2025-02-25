#include "Delaying.h"
#include "Clock.h"
#include "Event.h"
#include "GameGlobals.h"
#include "AbstractAction.h"
#include <QVariant>

Delaying::Delaying(AbstractGameObject *parent) :
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

void Delaying::addAction(AbstractAction *action)
{
	if (_actions.contains(action))
		return;

	_actions.append(action);
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

void Delaying::performActions()
{
	if (increaseTime() && delayDurationExceeded())
		for (auto *action : std::as_const(_actions))
			action->trigger();
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
