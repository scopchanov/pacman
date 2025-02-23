#include "DeenergizePlayer.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "objects/Player.h"

DeenergizePlayer::DeenergizePlayer(AbstractBehavior *parent) :
	AbstractAction{parent}
{

}

int DeenergizePlayer::type() const
{
	return ACT_DeenergizePlayer;
}

void DeenergizePlayer::performTask()
{
	Game::ref().level()->player()->deenergize();
}
