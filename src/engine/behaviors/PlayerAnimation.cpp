#include "PlayerAnimation.h"
#include "PathBuilder.h"

PlayerAnimation::PlayerAnimation(GameObject *parent) :
	AbstractAnimationBehavior(parent)
{
	setPathType(PathBuilder::GO_Player);
	setFrameRate(150);
}

void PlayerAnimation::reset()
{
	setValue(45);
	setDirection(DIR_Forwards);
	updateParent();
}

void PlayerAnimation::update()
{
	if (value() > 45)
		setValue(0);
}
