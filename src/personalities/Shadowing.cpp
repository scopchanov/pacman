#include "Shadowing.h"
#include "GameObject.h"
#include "Grid.h"
#include "Vector2.h"

Shadowing::Shadowing(GameObject *parent) :
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
