#include "AbstractBehavior.h"

AbstractBehavior::AbstractBehavior(GameObject *parent) :
	_parent{parent},
	_enabled{true}
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

bool AbstractBehavior::isEnabled() const
{
	return _enabled;
}

void AbstractBehavior::setEnabled(bool enabled)
{
	_enabled = enabled;
}

void AbstractBehavior::reset()
{

}

void AbstractBehavior::execute()
{
	if (!_parent || !_enabled)
		return;

	performActions();
}

void AbstractBehavior::performActions()
{

}
