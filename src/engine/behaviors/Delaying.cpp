#include "Delaying.h"
#include "engine/GameClock.h"
#include "engine/actions/AbstractAction.h"

Delaying::Delaying(GameObject *parent) :
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

void Delaying::performTimedActions()
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
