#include "Speeding.h"
#include "engine/objects/GameObject.h"
#include "engine/Grid.h"
#include "engine/Vector2.h"
#include "engine/behaviors/CharacterMovement.h"

Speeding::Speeding(GameObject *parent) :
	AbstractPersonality(parent)
{

}

int Speeding::type() const
{
	return PT_Speeding;
}

Vector2 Speeding::calculateTarget() const
{
	auto *behavior{player()->findBehavior(AbstractBehavior::BT_CharacterMovement)};

	if (!behavior)
		return Vector2();

	auto *movement{static_cast<CharacterMovement *>(behavior)};
	const Vector2 &playerDirection(movement->currentDirection());
	const Vector2 &targetCell{playerCell() + playerDirection*4};

	return grid()->mapFromGrid(targetCell);
}
