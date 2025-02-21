#include "Character.h"
#include "GameGlobals.h"
#include "behaviors/CharacterMovement.h"
#include <QPen>

Character::Character(GameObject *parent) :
	GameObject(parent)
{

}

void Character::setSpeed(qreal percent)
{
	auto *behavior{findBehavior(BT_CharacterMovement)};
	qreal originalSpeed{75.75757625};
	qreal nominalSpeed{3*originalSpeed};
	qreal speed{percent*nominalSpeed*0.01};

	static_cast<CharacterMovement *>(behavior)->setSpeed(speed);
}
