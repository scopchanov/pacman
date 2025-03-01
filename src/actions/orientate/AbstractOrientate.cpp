#include "AbstractOrientate.h"
#include "GameGlobals.h"

AbstractOrientate::AbstractOrientate(AbstractComponent *parent) :
	AbstractAction(parent),
	_move{nullptr}
{

}

Move *AbstractOrientate::move() const
{
	return _move;
}

void AbstractOrientate::setMove(Move *move)
{
	_move = move;
}

int AbstractOrientate::type() const
{
	return ACT_Orientate;
}

void AbstractOrientate::performTasks()
{
	if (!_move)
		return;

	orientate();
}
