#include "AbstractControl.h"
#include "GameGlobals.h"

AbstractControl::AbstractControl(AbstractComponent *parent) :
	AbstractAction(parent),
	_move{nullptr}
{

}

Move *AbstractControl::move() const
{
	return _move;
}

void AbstractControl::setMove(Move *move)
{
	_move = move;
}

int AbstractControl::type() const
{
	return ACT_Control;
}

void AbstractControl::performTasks()
{
	if (!_move)
		return;

	control();
}
