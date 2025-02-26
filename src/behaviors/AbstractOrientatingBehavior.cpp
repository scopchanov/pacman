#include "AbstractOrientatingBehavior.h"
#include "GameGlobals.h"

AbstractOrientatingBehavior::AbstractOrientatingBehavior(AbstractComponent *parent) :
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
	performTasks();
}

void AbstractOrientatingBehavior::performTasks()
{
	if (!_moving)
		return;

	performOrientationActions();
}
