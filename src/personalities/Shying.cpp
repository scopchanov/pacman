#include "Shying.h"
#include "GameGlobals.h"
#include "Grid.h"
#include "Vector2.h"
#include "behaviors/Moving.h"
#include "objects/Player.h"

Shying::Shying(AbstractGameObject *parent) :
	AbstractPersonality(parent),
	_partner{nullptr}
{

}

AbstractGameObject *Shying::partner() const
{
	return _partner;
}

void Shying::setPartner(AbstractGameObject *partner)
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

	auto *component{player()->findComponent(BT_Moving)};

	if (!component)
		return Vector2();

	auto *moving{static_cast<Moving *>(component)};
	const Vector2 &playerDirection(moving->currentDirection());
	const Vector2 &referenceCell{playerCell() + playerDirection*2};
	const Vector2 &reference{grid()->mapFromGrid(referenceCell)};

	return Vector2(_partner->pos() - reference).reversed() + reference;
}
