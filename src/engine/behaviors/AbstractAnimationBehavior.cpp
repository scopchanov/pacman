#include "AbstractAnimationBehavior.h"
#include "engine/GameObject.h"
#include "engine/GameTimer.h"

AbstractAnimationBehavior::AbstractAnimationBehavior(GameObject *parent) :
	AbstractTimedBehavior(parent),
	_frameTime{100},
	_value{0},
	_direction{DIR_Forwards}
{

}

qreal AbstractAnimationBehavior::frameTime() const
{
	return _frameTime;
}

void AbstractAnimationBehavior::setFrameTime(qreal frameTime)
{
	_frameTime = frameTime;
}

qreal AbstractAnimationBehavior::value() const
{
	return _value;
}

void AbstractAnimationBehavior::setValue(qreal value)
{
	_value = value;
}

AbstractAnimationBehavior::DirectionType AbstractAnimationBehavior::direction() const
{
	return _direction;
}

void AbstractAnimationBehavior::setDirection(DirectionType direction)
{
	_direction = direction;
}

int AbstractAnimationBehavior::type() const
{
	return BT_Animation;
}

void AbstractAnimationBehavior::performTimedActions()
{
	_value += _direction*_frameTime*gameTimer()->deltaTime();

	foo();
	updateParent();
}
