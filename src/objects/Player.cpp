#include "Player.h"
#include "AbstractBehavior.h"
#include "GameGlobals.h"
#include <QBrush>

Player::Player(GameObject *parent) :
	Character(parent)
{

}

void Player::energize()
{
	setSpeed(90);
	setBrush(QBrush(0xE040FB));
	findBehavior(BT_EnemyEating)->setEnabled(true);
}

void Player::deenergize()
{
	setSpeed(80);
	setBrush(QBrush(0xFFFFFF));
	findBehavior(BT_EnemyEating)->setEnabled(false);
}

int Player::objectType() const
{
	return OBJ_Player;
}
