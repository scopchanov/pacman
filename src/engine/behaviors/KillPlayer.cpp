#include "KillPlayer.h"
#include "engine/Game.h"
#include "engine/GameEvent.h"
#include "engine/objects/GameObject.h"

KillPlayer::KillPlayer(GameObject *parent) :
	AbstractTimedBehavior(parent),
	_eventPlayerDies{nullptr}
{

}

void KillPlayer::setEventPlayerDies(GameEvent *gameEvent)
{
	_eventPlayerDies = gameEvent;
}

int KillPlayer::type() const
{
	return BT_KillPlayer;
}

void KillPlayer::performActions()
{
	if (parent()->collidesWithItem(Game::ref().player()) && _eventPlayerDies)
		_eventPlayerDies->trigger();
}
