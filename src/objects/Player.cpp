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
	foo(90, Game::ref().palette()->color(CR_PlayerEnergized), true);
}

void Player::deenergize()
{
	foo(80, Game::ref().palette()->color(CR_Player), false);
}

int Player::objectType() const
{
	return OBJ_Player;
}

void Player::foo(qreal speed, const QColor &color, bool eatEnemy)
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
