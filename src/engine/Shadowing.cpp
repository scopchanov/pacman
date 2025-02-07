#include "Shadowing.h"
#include "GameObject.h"
#include "Vector2.h"

Shadowing::Shadowing() :
	AbstractChasingStrategy()
{

}

Vector2 Shadowing::calculateTargetPosition() const
{
	return Vector2(player()->pos());
}
