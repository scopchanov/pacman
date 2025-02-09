#include "PlayerAnimation.h"
#include "PathBuilder.h"
#include "engine/GameObject.h"

PlayerAnimation::PlayerAnimation(GameObject *parent) :
	AbstractAnimationBehavior(parent)
{

}

void PlayerAnimation::reset()
{
	setValue(45);
	setDirection(DIR_Forwards);
	updateParent();
}

void PlayerAnimation::foo()
{
	if (value() >= 45)
		setValue(0);
}

void PlayerAnimation::updateParent()
{
	parent()->setPath(PathBuilder::playerPath(value()));
	parent()->update();
}
