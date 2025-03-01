#include "AbstractTimedAction.h"
#include "Game.h"

AbstractTimedAction::AbstractTimedAction(AbstractComponent *parent) :
	AbstractAction(parent)
{

}

Clock *AbstractTimedAction::clock() const
{
	return Game::ref().clock();
}
