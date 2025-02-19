#include "KillPlayer.h"
#include "Game.h"
#include "GameEvent.h"
#include "GameGlobals.h"
#include "GameObject.h"

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
	if (parent()->collidesWithObject(Game::ref().player()) && _eventPlayerDies)
		_eventPlayerDies->trigger();
}
