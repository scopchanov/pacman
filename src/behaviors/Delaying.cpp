#include "Delaying.h"
#include "GameClock.h"
#include "GameGlobals.h"
#include "AbstractAction.h"

Delaying::Delaying(AbstractGameObject *parent) :
	AbstractTimedBehavior(parent),
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

void Delaying::addAction(AbstractAction *action)
{
	if (_actions.contains(action))
		return;

	_actions.append(action);
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

	return true;
}

bool Delaying::delayDurationExceeded() const
{
	return _time >= _duration;
}
