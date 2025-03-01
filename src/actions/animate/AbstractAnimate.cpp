#include "AbstractAnimate.h"
#include "Clock.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "PathBuilder.h"

AbstractAnimate::AbstractAnimate(AbstractComponent *parent) :
	AbstractTimedAction(parent),
	_frameRate{100},
	_direction{DIR_Forwards},
	_value{0}
{

}

qreal AbstractAnimate::frameRate() const
{
	return _frameRate;
}

void AbstractAnimate::setFrameRate(qreal frameRate)
{
	_frameRate = frameRate;
}

qreal AbstractAnimate::value() const
{
	return _value;
}

void AbstractAnimate::setValue(qreal value)
{
	_value = value;
}

AbstractAnimate::DirectionType AbstractAnimate::direction() const
{
	return _direction;
}

void AbstractAnimate::setDirection(DirectionType direction)
{
	_direction = direction;
}

int AbstractAnimate::type() const
{
	return ACT_Animate;
}

void AbstractAnimate::performTasks()
{
	_value += _direction*_frameRate*clock()->deltaTime();

	update();
	updateParent();
}

void AbstractAnimate::updateParent()
{
	int pathType{gameObject()->objectType()};

	gameObject()->setPath(PathBuilder::dynamicObjectPath(pathType, _value));
	gameObject()->update();
}
