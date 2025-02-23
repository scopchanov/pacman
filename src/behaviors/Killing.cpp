#include "Killing.h"
#include "Game.h"
#include "GameEvent.h"
#include "GameLevel.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "objects/Player.h"

Killing::Killing(AbstractGameObject *parent) :
	AbstractTimedBehavior(parent),
	_eventPlayerDies{nullptr}
{

}

void Killing::setEventPlayerDies(GameEvent *gameEvent)
{
	_eventPlayerDies = gameEvent;
}

int Killing::type() const
{
	return BT_Killing;
}

void Killing::performActions()
{
	if (parent()->collidesWithObject(Game::ref().level()->player()) && _eventPlayerDies)
		_eventPlayerDies->trigger();
}
