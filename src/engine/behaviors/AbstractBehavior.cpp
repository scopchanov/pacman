#include "AbstractBehavior.h"

AbstractBehavior::AbstractBehavior(GameObject *parent) :
	_parent{parent}
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

void AbstractBehavior::reset()
{

}

void AbstractBehavior::execute()
{
	if (!_parent)
		return;

	performActions();
}
