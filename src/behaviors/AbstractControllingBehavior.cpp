#include "AbstractControllingBehavior.h"
#include "GameGlobals.h"

AbstractControllingBehavior::AbstractControllingBehavior(GameObject *parent) :
	AbstractBehavior(parent),
	_moving{nullptr}
{

}

Moving *AbstractControllingBehavior::moving() const
{
	return _moving;
}

void AbstractControllingBehavior::setMoving(Moving *moving)
{
	_moving = moving;
}

int AbstractControllingBehavior::type() const
{
	return BT_Controlling;
}

void AbstractControllingBehavior::performActions()
{
	if (!_moving)
		return;

	performControllingActions();
}
