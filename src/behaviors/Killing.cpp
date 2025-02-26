#include "Killing.h"
#include "Game.h"
#include "Event.h"
#include "GameLevel.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "objects/Player.h"

Killing::Killing(AbstractComponent *parent) :
	AbstractTimedBehavior(parent),
	_eventPlayerDied{nullptr}
{

}

void Killing::setEventPlayerDied(Event *event)
{
	_eventPlayerDied = event;
}

int Killing::type() const
{
	return BT_Killing;
}

void Killing::performTasks()
{
	auto *player{Game::ref().level()->player()};

	if (_eventPlayerDied && gameObject()->collidesWithObject(player))
		_eventPlayerDied->trigger();
}
