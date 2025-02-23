#include "EnemyAnimating.h"
#include "GameObject.h"
#include "PathBuilder.h"

EnemyAnimating::EnemyAnimating(GameObject *parent) :
	AbstractAnimatingBehavior(parent)
{
	setPathType(PathBuilder::GO_Enemy);
	setFrameRate(20);
}

void EnemyAnimating::update()
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
