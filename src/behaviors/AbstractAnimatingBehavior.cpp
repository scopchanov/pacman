#include "AbstractAnimatingBehavior.h"
#include "GameClock.h"
#include "GameGlobals.h"
#include "GameObject.h"
#include "PathBuilder.h"

AbstractAnimatingBehavior::AbstractAnimatingBehavior(GameObject *parent) :
	AbstractTimedBehavior(parent),
	_gameObjectType{0},
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

int AbstractAnimatingBehavior::gameObjectType() const
{
	return _gameObjectType;
}

void AbstractAnimatingBehavior::setPathType(int type)
{
	_gameObjectType = type;
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
	auto type{static_cast<PathBuilder::GameObjectType>(_gameObjectType)};

	parent()->setPath(PathBuilder::animatedObjectPath(type, _value));
	parent()->update();
}

void AbstractAnimatingBehavior::performActions()
{
	_value += _direction*_frameRate*clock()->deltaTime();

	update();
	updateParent();
}
