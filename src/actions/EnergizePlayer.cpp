#include "EnergizePlayer.h"
#include "Game.h"
#include "GameLevel.h"
#include "GameGlobals.h"
#include "objects/Player.h"

EnergizePlayer::EnergizePlayer(AbstractComponent *parent) :
	AbstractAction{parent}
{

}

int EnergizePlayer::type() const
{
	return ACT_EnergizePlayer;
}

void EnergizePlayer::performTasks()
{
	Game::ref().level()->player()->energize();
}
