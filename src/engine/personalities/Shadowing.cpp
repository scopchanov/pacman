#include "Shadowing.h"
#include "engine/objects/GameObject.h"
#include "engine/Grid.h"
#include "engine/Vector2.h"

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
