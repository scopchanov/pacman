#include "EnemyAnimation.h"
#include "PathBuilder.h"
#include "engine/GameObject.h"

EnemyAnimation::EnemyAnimation(GameObject *parent) :
	AbstractAnimationBehavior(parent)
{

}

void EnemyAnimation::reset()
{
	setValue(0);
	setDirection(DIR_Forwards);
	updateParent();
}

void EnemyAnimation::foo()
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

void EnemyAnimation::updateParent()
{
	parent()->setPath(PathBuilder::enemyPath(value()));
	parent()->update();
}
