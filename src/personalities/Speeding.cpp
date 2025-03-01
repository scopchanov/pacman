#include "Speeding.h"
#include "GameGlobals.h"
#include "Grid.h"
#include "actions/tilemap/Move.h"
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
	auto *component{player()->findComponent(ACT_Move)};

	if (!component)
		return Vector2();

	auto *move{static_cast<Move *>(component)};
	const Vector2 &playerDirection(move->currentDirection());
	const Vector2 &targetCell{playerCell() + playerDirection*4};

	return grid()->mapFromGrid(targetCell);
}
