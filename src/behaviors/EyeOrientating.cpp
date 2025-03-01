#include "EyeOrientating.h"
#include "Moving.h"
#include "AbstractGameObject.h"
#include "objects/EnemyEye.h"

EyeOrientating::EyeOrientating(AbstractComponent *parent) :
	AbstractOrientatingBehavior(parent)
{

}

void EyeOrientating::reset()
{
	enemyEye()->setDirection(currentDirection());
}

void EyeOrientating::performOrientationActions()
{
	enemyEye()->orientate(currentDirection());
}

Vector2 EyeOrientating::currentDirection()
{
	return moving() ? moving()->currentDirection() : Vector2();
}

EnemyEye *EyeOrientating::enemyEye() const
{
	return static_cast<EnemyEye *>(gameObject());
}
