#include "EnergizePlayer.h"
#include "AbstractBehavior.h"
#include "Game.h"
#include "objects/Player.h"
#include "GameGlobals.h"
#include <QBrush>

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
	auto *player{Game::ref().player()};

	player->setSpeed(90);
	player->setBrush(QBrush(0xE040FB));
	player->findBehavior(BT_EnemyEating)->setEnabled(true);
}
