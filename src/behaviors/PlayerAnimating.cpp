#include "PlayerAnimating.h"
#include "PathBuilder.h"

PlayerAnimating::PlayerAnimating(GameObject *parent) :
	AbstractAnimatingBehavior(parent)
{
	setPathType(PathBuilder::GO_Player);
	setFrameRate(150);
}

void PlayerAnimating::reset()
{
	setValue(45);
	setDirection(DIR_Forwards);
	updateParent();
}

void PlayerAnimating::update()
{
	if (value() > 45)
		setValue(0);
}
