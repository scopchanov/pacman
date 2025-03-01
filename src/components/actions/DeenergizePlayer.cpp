#include "DeenergizePlayer.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "objects/Player.h"

DeenergizePlayer::DeenergizePlayer(AbstractComponent *parent) :
	AbstractAction{parent}
{

}

int DeenergizePlayer::type() const
{
	return ACT_DeenergizePlayer;
}

void DeenergizePlayer::performTasks()
{
	Game::ref().level()->player()->deenergize();
}
