#include "AbstractBehavior.h"
#include "engine/actions/AbstractAction.h"

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

void AbstractBehavior::addAction(AbstractAction *action)
{
	if (_actions.contains(action))
		return;

	_actions.append(action);
}

AbstractAction *AbstractBehavior::findAction(int type) const
{
	for (auto *action : std::as_const(_actions))
		if (action->type() == type)
			return action;

	return nullptr;
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
