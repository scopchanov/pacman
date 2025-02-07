#include "Shadowing.h"
#include "engine/GameObject.h"
#include "engine/Vector2.h"

Shadowing::Shadowing(QObject *parent) :
	AbstractPersonality(parent)
{

}

Vector2 Shadowing::calculateTargetPosition() const
{
	return Vector2(player()->pos());
}
