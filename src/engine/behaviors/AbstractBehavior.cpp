#include "AbstractBehavior.h"

AbstractBehavior::AbstractBehavior(GameObject *parent) :
	_parent{parent},
	_disabled{false}
{

}

GameObject *AbstractBehavior::parent() const
{
	return _parent;
}

void AbstractBehavior::setParent(GameObject *parent)
{
	_parent = parent;
}

bool AbstractBehavior::isDisabled() const
{
	return _disabled;
}

void AbstractBehavior::setDisabled(bool value)
{
	_disabled = value;
}

void AbstractBehavior::reset()
{

}

void AbstractBehavior::execute()
{
	if (!_parent || _disabled)
		return;

	performActions();
}
