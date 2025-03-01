#include "AbstractControl.h"
#include "GameGlobals.h"

AbstractControl::AbstractControl(AbstractComponent *parent) :
	AbstractAction(parent),
	_moving{nullptr}
{

}

Moving *AbstractControl::moving() const
{
	return _moving;
}

void AbstractControl::setMoving(Moving *moving)
{
	_moving = moving;
}

int AbstractControl::type() const
{
	return ACT_Control;
}

void AbstractControl::performTasks()
{
	if (!_moving)
		return;

	control();
}
