#include "AbstractAnimatingBehavior.h"
#include "GameClock.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "PathBuilder.h"

AbstractAnimatingBehavior::AbstractAnimatingBehavior(AbstractGameObject *parent) :
	AbstractTimedBehavior(parent),
	_frameRate{100},
	_direction{DIR_Forwards},
	_value{0}
{

}

qreal AbstractAnimatingBehavior::frameRate() const
{
	return _frameRate;
}

void AbstractAnimatingBehavior::setFrameRate(qreal frameRate)
{
	_frameRate = frameRate;
}

qreal AbstractAnimatingBehavior::value() const
{
	return _value;
}

void AbstractAnimatingBehavior::setValue(qreal value)
{
	_value = value;
}

AbstractAnimatingBehavior::DirectionType AbstractAnimatingBehavior::direction() const
{
	return _direction;
}

void AbstractAnimatingBehavior::setDirection(DirectionType direction)
{
	_direction = direction;
}

int AbstractAnimatingBehavior::type() const
{
	return BT_Animating;
}

void AbstractAnimatingBehavior::reset()
{
	setValue(0);
	setDirection(DIR_Forwards);
	updateParent();
}

void AbstractAnimatingBehavior::updateParent()
{
	int pathType{parent()->objectType()};

	parent()->setPath(PathBuilder::animatedObjectPath(pathType, _value));
	parent()->update();
}

void AbstractAnimatingBehavior::performActions()
{
	_value += _direction*_frameRate*clock()->deltaTime();

	update();
	updateParent();
}
