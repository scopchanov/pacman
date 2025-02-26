#include "AbstractControllingBehavior.h"
#include "GameGlobals.h"

AbstractControllingBehavior::AbstractControllingBehavior(AbstractComponent *parent) :
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

void AbstractControllingBehavior::performTasks()
{
	if (!_moving)
		return;

	performControllingActions();
}
