#include "EnergizePlayer.h"
#include "engine/Game.h"
#include "engine/Player.h"
#include "engine/behaviors/AbstractBehavior.h"
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

	player->setBrush(QBrush(0xE040FB));
	player->findBehavior(AbstractBehavior::BT_EnemyEating)->setEnabled(true);
}
