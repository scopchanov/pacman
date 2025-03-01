#include "OrientateEye.h"
#include "AbstractGameObject.h"
#include "behaviors/Moving.h"
#include "objects/EnemyEye.h"

OrientateEye::OrientateEye(AbstractComponent *parent) :
	AbstractOrientate(parent)
{

}

void OrientateEye::reset()
{
	enemyEye()->setDirection(currentDirection());
}

void OrientateEye::orientate()
{
	enemyEye()->orientate(currentDirection());
}

Vector2 OrientateEye::currentDirection()
{
	return moving() ? moving()->currentDirection() : Vector2();
}

EnemyEye *OrientateEye::enemyEye() const
{
	return static_cast<EnemyEye *>(gameObject());
}
