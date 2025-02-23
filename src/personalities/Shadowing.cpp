#include "Shadowing.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "Grid.h"
#include "Vector2.h"

Shadowing::Shadowing(AbstractGameObject *parent) :
	AbstractPersonality(parent)
{

}

int Shadowing::type() const
{
	return PT_Shadowing;
}

Vector2 Shadowing::calculateTarget() const
{
	return Vector2(grid()->mapFromGrid(playerCell()));
}
