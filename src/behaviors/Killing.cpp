#include "Killing.h"
#include "Game.h"
#include "Event.h"
#include "GameLevel.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "objects/Player.h"

Killing::Killing(AbstractGameObject *parent) :
	AbstractTimedBehavior(parent),
	_eventPlayerDies{nullptr}
{

}

void Killing::setEventPlayerDies(Event *event)
{
	_eventPlayerDies = event;
}

int Killing::type() const
{
	return BT_Killing;
}

void Killing::performActions()
{
	auto *player{Game::ref().level()->player()};

	if (_eventPlayerDies && parent()->collidesWithObject(player))
		_eventPlayerDies->trigger();
}
