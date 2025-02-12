#include "PowerUpAnimation.h"
#include "PathBuilder.h"

PowerUpAnimation::PowerUpAnimation(GameObject *parent) :
	AbstractAnimationBehavior(parent)
{
	setValue(8);
	setFrameRate(15);
	setGameObjectType(PathBuilder::GO_PowerUp);
}

void PowerUpAnimation::update()
{
	if (value() > 16)
		setValue(8);
}
