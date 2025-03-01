#include "EyeOrientate.h"
#include "AbstractGameObject.h"
#include "behaviors/Moving.h"
#include "objects/EnemyEye.h"

EyeOrientate::EyeOrientate(AbstractComponent *parent) :
	AbstractOrientate(parent)
{

}

void EyeOrientate::reset()
{
	enemyEye()->setDirection(currentDirection());
}

void EyeOrientate::orientate()
{
	enemyEye()->orientate(currentDirection());
}

Vector2 EyeOrientate::currentDirection()
{
	return moving() ? moving()->currentDirection() : Vector2();
}

EnemyEye *EyeOrientate::enemyEye() const
{
	return static_cast<EnemyEye *>(gameObject());
}
