#include "KillPlayer.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "objects/Player.h"

KillPlayer::KillPlayer(AbstractComponent *parent) :
	AbstractAction(parent)
{

}

int KillPlayer::type() const
{
	return ACT_KillPlayer;
}

void KillPlayer::performTasks()
{
	auto *player{Game::ref().level()->player()};

	if (gameObject()->collidesWithObject(player))
		emit playerDied();
}
