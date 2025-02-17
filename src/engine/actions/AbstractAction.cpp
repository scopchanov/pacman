#include "AbstractAction.h"

AbstractAction::AbstractAction(AbstractBehavior *parent) :
	_parent{parent},
	_game{nullptr}
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

Game *AbstractAction::game() const
{
	return _game;
}

void AbstractAction::setGame(Game *game)
{
	_game = game;
}

void AbstractAction::trigger()
{
	if (!_parent || !_game)
		return;

	performTask();
}
