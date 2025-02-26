#include "PlayerAnimating.h"

PlayerAnimating::PlayerAnimating(AbstractComponent *parent) :
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
