#include "PlayerAnimating.h"

PlayerAnimating::PlayerAnimating(AbstractGameObject *parent) :
	AbstractAnimatingBehavior(parent)
{
	setFrameRate(150);
}

void PlayerAnimating::reset()
{
	setValue(45);
	updateParent();
}

void PlayerAnimating::update()
{
	if (value() > 45)
		setValue(0);
}
