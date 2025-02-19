#include "AbstractAnimationBehavior.h"
#include "GameClock.h"
#include "GameGlobals.h"
#include "GameObject.h"
#include "PathBuilder.h"

AbstractAnimationBehavior::AbstractAnimationBehavior(GameObject *parent) :
	AbstractTimedBehavior(parent),
	_gameObjectType{0},
	_frameRate{100},
	_direction{DIR_Forwards},
	_value{0}
{

}

qreal AbstractAnimationBehavior::frameRate() const
{
	return _frameRate;
}

void AbstractAnimationBehavior::setFrameRate(qreal frameRate)
{
	_frameRate = frameRate;
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

int AbstractAnimationBehavior::gameObjectType() const
{
	return _gameObjectType;
}

void AbstractAnimationBehavior::setPathType(int type)
{
	_gameObjectType = type;
}

int AbstractAnimationBehavior::type() const
{
	return BT_Animation;
}

void AbstractAnimationBehavior::reset()
{
	setValue(0);
	setDirection(DIR_Forwards);
	updateParent();
}

void AbstractAnimationBehavior::updateParent()
{
	auto type{static_cast<PathBuilder::GameObjectType>(_gameObjectType)};

	parent()->setPath(PathBuilder::animatedObjectPath(type, _value));
	parent()->update();
}

void AbstractAnimationBehavior::performActions()
{
	_value += _direction*_frameRate*clock()->deltaTime();

	update();
	updateParent();
}
