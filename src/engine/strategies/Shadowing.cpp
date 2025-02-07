#include "Shadowing.h"
#include "engine/GameObject.h"
#include "engine/Vector2.h"

Shadowing::Shadowing() :
	AbstractChasingStrategy()
{

}

Vector2 Shadowing::calculateTargetPosition() const
{
	return Vector2(player()->pos());
}
