#include "Player.h"
#include "AbstractComponent.h"
#include "Game.h"
#include "GameGlobals.h"
#include <QBrush>

Player::Player(AbstractGameObject *parent) :
	AbstractCharacter(parent)
{

}

void Player::energize()
{
	mutate(90, paletteColor(CR_PlayerEnergized), true);
}

void Player::deenergize()
{
	mutate(80, paletteColor(CR_Player), false);
}

int Player::objectType() const
{
	return OBJ_Player;
}

int Player::colorRole() const
{
	return CR_Player;
}

void Player::mutate(qreal speed, const QColor &color, bool eatEnemy)
{
	setSpeed(speed);
	setBrush(color);
	enableEatEnemy(eatEnemy);
}

void Player::enableEatEnemy(bool enable)
{
	auto *eatEnemy{findComponent(ACT_EatEnemy)};

	if (!eatEnemy)
		return;

	eatEnemy->setEnabled(enable);
	eatEnemy->reset();
}
