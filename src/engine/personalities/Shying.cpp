#include "Shying.h"
#include "engine/objects/GameObject.h"
#include "engine/Grid.h"
#include "engine/Vector2.h"
#include "engine/behaviors/CharacterMovement.h"

Shying::Shying(GameObject *parent) :
	AbstractPersonality(parent),
	_partner{nullptr}
{

}

GameObject *Shying::partner() const
{
	return _partner;
}

void Shying::setPartner(GameObject *partner)
{
	_partner = partner;
}

int Shying::type() const
{
	return PT_Shying;
}

Vector2 Shying::calculateTarget() const
{
	if (!_partner)
		return Vector2();

	auto *behavior{player()->findBehavior(AbstractBehavior::BT_CharacterMovement)};

	if (!behavior)
		return Vector2();

	auto *movement{static_cast<CharacterMovement *>(behavior)};
	const Vector2 &playerDirection(movement->currentDirection());
	const Vector2 &referenceCell{playerCell() + playerDirection*2};
	const Vector2 &reference{grid()->mapFromGrid(referenceCell)};

	return Vector2(_partner->pos() - reference).reversed() + reference;
}
