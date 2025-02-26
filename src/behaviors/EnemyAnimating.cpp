#include "EnemyAnimating.h"

EnemyAnimating::EnemyAnimating(AbstractComponent *parent) :
	AbstractAnimatingBehavior(parent)
{
	setFrameRate(20);
}

void EnemyAnimating::reset()
{
	setValue(0);
	setDirection(DIR_Forwards);
	updateParent();
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
