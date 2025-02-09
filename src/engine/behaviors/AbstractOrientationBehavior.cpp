#include "AbstractOrientationBehavior.h"

AbstractOrientationBehavior::AbstractOrientationBehavior(GameObject *parent) :
	AbstractBehavior(parent),
	_movement{nullptr}
{

}

CharacterMovement *AbstractOrientationBehavior::movement() const
{
	return _movement;
}

void AbstractOrientationBehavior::setMovement(CharacterMovement *movement)
{
	_movement = movement;
}

int AbstractOrientationBehavior::type() const
{
	return BT_Orientation;
}

void AbstractOrientationBehavior::reset()
{
	performActions();
}

void AbstractOrientationBehavior::performActions()
{
	if (!_movement)
		return;

	performOrientationActions();
}
