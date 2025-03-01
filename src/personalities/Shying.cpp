#include "Shying.h"
#include "GameGlobals.h"
#include "Grid.h"
#include "Vector2.h"
#include "actions/tilemap/Move.h"
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

	auto *component{player()->findComponent(ACT_Move)};

	if (!component)
		return Vector2();

	auto *move{static_cast<Move *>(component)};
	const Vector2 &playerDirection(move->currentDirection());
	const Vector2 &referenceCell{playerCell() + playerDirection*2};
	const Vector2 &reference{grid()->mapFromGrid(referenceCell)};

	return Vector2(_partner->pos() - reference).reversed() + reference;
}
