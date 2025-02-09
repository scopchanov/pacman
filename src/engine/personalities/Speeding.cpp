#include "Speeding.h"
#include "engine/GameObject.h"
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
	Vector2 playerCell(grid()->posToCell(player()->pos()));
	auto *behavior{player()->findBehavior(AbstractBehavior::BT_CharacterMovement)};

	if (!behavior)
		return Vector2();

	auto *movement{static_cast<CharacterMovement *>(behavior)};
	const Vector2 &playerDirection(movement->currentDirection());
	const Vector2 &fcbp{playerCell + playerDirection*4};

	return grid()->cellPosition(fcbp);
}
