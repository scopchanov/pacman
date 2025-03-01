#include "AnimateEnemy.h"

AnimateEnemy::AnimateEnemy(AbstractComponent *parent) :
	AbstractAnimate(parent)
{
	setFrameRate(20);
}

void AnimateEnemy::reset()
{
	setValue(0);
	setDirection(DIR_Forwards);
	updateParent();
}

void AnimateEnemy::update()
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
