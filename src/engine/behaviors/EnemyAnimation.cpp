#include "EnemyAnimation.h"
#include "PathBuilder.h"
#include "engine/GameObject.h"

EnemyAnimation::EnemyAnimation(GameObject *parent) :
	AbstractAnimationBehavior(parent)
{
	setGameObjectType(PathBuilder::GO_Enemy);
	setFrameRate(20);
}

void EnemyAnimation::update()
{
	// TODO: Improve the method's name

	if (value() > 2) {
		setValue(2);
		setDirection(DIR_Backwards);
	}

	if (value() < -2) {
		setValue(-2);
		setDirection(DIR_Forwards);
	}
}
