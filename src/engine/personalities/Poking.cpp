#include "Poking.h"
#include "engine/GameObject.h"
#include "engine/Grid.h"
#include "engine/Vector2.h"

Poking::Poking(GameObject *parent) :
	AbstractPersonality(parent)
{

}

int Poking::type() const
{
	return PT_Poking;
}

Vector2 Poking::calculateTarget() const
{
	qreal distance{Vector2(parent()->pos()).distanceTo(player()->pos())};
	qreal maxDistance{8*grid()->cellSize().width()};
	bool isClose{distance <= maxDistance};

	return Vector2(isClose ? scatterTarget() : grid()->cellPosition(playerCell()));
}
