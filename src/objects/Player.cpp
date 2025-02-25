#include "Player.h"
#include "AbstractBehavior.h"
#include "Game.h"
#include "GameGlobals.h"
#include "Palette.h"
#include <QBrush>

Player::Player(AbstractGameObject *parent) :
	Character(parent)
{

}

void Player::energize()
{
	setSpeed(90);
	setBrush(Game::ref().palette()->color(CR_PlayerEnergized));
	enableEnemyEating(true);
}

void Player::deenergize()
{
	setSpeed(80);
	setBrush(Game::ref().palette()->color(CR_Player));
	enableEnemyEating(false);
}

int Player::objectType() const
{
	return OBJ_Player;
}

void Player::enableEnemyEating(bool enable)
{
	auto *enemyEating{findBehavior(BT_EnemyEating)};

	if (enemyEating)
		enemyEating->setEnabled(enable);
}
