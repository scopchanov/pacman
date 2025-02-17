#include "KillPlayer.h"
#include "engine/GameEvent.h"
#include "engine/objects/GameObject.h"

KillPlayer::KillPlayer(GameObject *parent) :
	AbstractTimedBehavior(parent),
	_player{nullptr},
	_eventPlayerDies{nullptr}
{

}

GameObject *KillPlayer::player() const
{
	return _player;
}

void KillPlayer::setPlayer(GameObject *player)
{
	_player = player;
}

void KillPlayer::setEventPlayerDies(GameEvent *gameEvent)
{
	_eventPlayerDies = gameEvent;
}

int KillPlayer::type() const
{
	return BT_KillPlayer;
}

void KillPlayer::performTimedActions()
{
	if (!_player)
		return;

	if (parent()->collidesWithItem(_player) && _eventPlayerDies)
		_eventPlayerDies->trigger();
}
