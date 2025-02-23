#include "AbstractOrientatingBehavior.h"
#include "GameGlobals.h"

AbstractOrientatingBehavior::AbstractOrientatingBehavior(GameObject *parent) :
	AbstractBehavior(parent),
	_moving{nullptr}
{

}

Moving *AbstractOrientatingBehavior::moving() const
{
	return _moving;
}

void AbstractOrientatingBehavior::setMoving(Moving *moving)
{
	_moving = moving;
}

int AbstractOrientatingBehavior::type() const
{
	return BT_Orientating;
}

void AbstractOrientatingBehavior::reset()
{
	performActions();
}

void AbstractOrientatingBehavior::performActions()
{
	if (!_moving)
		return;

	performOrientationActions();
}
