#include "AbstractOrientate.h"
#include "GameGlobals.h"

AbstractOrientate::AbstractOrientate(AbstractComponent *parent) :
	AbstractAction(parent),
	_moving{nullptr}
{

}

Moving *AbstractOrientate::moving() const
{
	return _moving;
}

void AbstractOrientate::setMoving(Moving *moving)
{
	_moving = moving;
}

int AbstractOrientate::type() const
{
	return ACT_Orientate;
}

void AbstractOrientate::performTasks()
{
	if (!_moving)
		return;

	orientate();
}
