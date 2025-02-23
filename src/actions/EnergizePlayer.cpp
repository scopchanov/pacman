#include "EnergizePlayer.h"
#include "Game.h"
#include "GameLevel.h"
#include "GameGlobals.h"
#include "objects/Player.h"

EnergizePlayer::EnergizePlayer(AbstractBehavior *parent) :
	AbstractAction{parent}
{

}

int EnergizePlayer::type() const
{
	return ACT_EnergizePlayer;
}

void EnergizePlayer::performTask()
{
	Game::ref().level()->player()->energize();
}
