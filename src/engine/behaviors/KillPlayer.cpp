#include "KillPlayer.h"
#include "engine/GameEvent.h"
#include "engine/GameObject.h"

KillPlayer::KillPlayer(GameObject *parent) :
	AbstractTimedBehavior(parent),
	m_player{nullptr},
	m_eventPlayerDies{nullptr}
{

}

GameObject *KillPlayer::player() const
{
	return m_player;
}

void KillPlayer::setPlayer(GameObject *player)
{
	m_player = player;
}

void KillPlayer::setEventPlayerDies(GameEvent *gameEvent)
{
	m_eventPlayerDies = gameEvent;
}

int KillPlayer::type() const
{
	return BT_KillPlayer;
}

void KillPlayer::reset()
{

}

void KillPlayer::performTimedActions()
{
	if (!m_player)
		return;

	if (parent()->collidesWithItem(m_player) && m_eventPlayerDies)
		m_eventPlayerDies->trigger();
}
