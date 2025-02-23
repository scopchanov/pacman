#include "EnemyAnimating.h"
#include "AbstractGameObject.h"

EnemyAnimating::EnemyAnimating(AbstractGameObject *parent) :
	AbstractAnimatingBehavior(parent)
{
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
