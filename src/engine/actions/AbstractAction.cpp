#include "AbstractAction.h"

AbstractAction::AbstractAction(AbstractBehavior *parent) :
	_parent{parent}
{

}

AbstractBehavior *AbstractAction::parent() const
{
	return _parent;
}

void AbstractAction::setParent(AbstractBehavior *parent)
{
	_parent = parent;
}

void AbstractAction::trigger()
{
	if (!_parent)
		return;

	performTask();
}
