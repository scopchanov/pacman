#include "AbstractAnimatingBehavior.h"
#include "Clock.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "PathBuilder.h"

AbstractAnimatingBehavior::AbstractAnimatingBehavior(AbstractComponent *parent) :
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

void AbstractAnimatingBehavior::performTasks()
{
	_value += _direction*_frameRate*clock()->deltaTime();

	update();
	updateParent();
}

void AbstractAnimatingBehavior::updateParent()
{
	int pathType{gameObject()->objectType()};

	gameObject()->setPath(PathBuilder::dynamicObjectPath(pathType, _value));
	gameObject()->update();
}
