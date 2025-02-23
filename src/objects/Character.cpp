#include "Character.h"
#include "GameGlobals.h"
#include "behaviors/Moving.h"
#include <QPen>

Character::Character(AbstractGameObject *parent) :
	AbstractGameObject(parent)
{

}

void Character::setSpeed(qreal percent)
{
	auto *behavior{findBehavior(BT_Moving)};
	qreal originalSpeed{75.75757625};
	qreal nominalSpeed{3*originalSpeed};
	qreal speed{percent*nominalSpeed*0.01};

	static_cast<Moving *>(behavior)->setSpeed(speed);
}
