#include "EnergizePlayer.h"
#include "Game.h"
#include "GameLevel.h"
#include "GameGlobals.h"
#include "objects/Deenergizer.h"
#include "objects/Enemy.h"
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
	if (!gameObject()->collidesWithObject(Game::ref().level()->player()))
		return;

	Game::ref().level()->player()->energize();

	const QList<Enemy *> &enemies{Game::ref().level()->enemies()};

	for (auto *enemy : enemies)
		if (enemy->state() != Enemy::ST_Eaten)
			enemy->scare();

	Game::ref().level()->deenergizer()->activate();
	gameObject()->deleteLater();

	emit playerEnergized(gameObject()->pos());
}
