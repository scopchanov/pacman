#include "DeenergizePlayer.h"
#include "engine/Game.h"
#include "engine/Player.h"
#include "engine/behaviors/AbstractBehavior.h"
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
	player->findBehavior(AbstractBehavior::BT_EnemyEating)->setEnabled(false);
}
