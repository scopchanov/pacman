#include "Speeding.h"
#include "GameGlobals.h"
#include "Grid.h"
#include "Vector2.h"
#include "behaviors/Moving.h"
#include "objects/Player.h"

Speeding::Speeding(AbstractGameObject *parent) :
	AbstractPersonality(parent)
{

}

int Speeding::type() const
{
	return PT_Speeding;
}

Vector2 Speeding::calculateTarget() const
{
	auto *behavior{player()->findBehavior(BT_Moving)};

	if (!behavior)
		return Vector2();

	auto *moving{static_cast<Moving *>(behavior)};
	const Vector2 &playerDirection(moving->currentDirection());
	const Vector2 &targetCell{playerCell() + playerDirection*4};

	return grid()->mapFromGrid(targetCell);
}
