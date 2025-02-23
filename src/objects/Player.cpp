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
	findBehavior(BT_EnemyEating)->setEnabled(true);
}

void Player::deenergize()
{
	setSpeed(80);
	setBrush(Game::ref().palette()->color(CR_Player));
	findBehavior(BT_EnemyEating)->setEnabled(false);
}

int Player::objectType() const
{
	return OBJ_Player;
}
