#include "DeenergizePlayer.h"
#include "AbstractBehavior.h"
#include "GameGlobals.h"
#include "Game.h"
#include "objects/Player.h"
#include <QBrush>

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
	auto *player{Game::ref().player()};

	player->setSpeed(80);
	player->setBrush(QBrush(0xFFFFFF));
	player->findBehavior(BT_EnemyEating)->setEnabled(false);
}
