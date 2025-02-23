#include "Poking.h"
#include "Grid.h"
#include "Vector2.h"
#include "objects/Player.h"
#include "GameGlobals.h"

Poking::Poking(AbstractGameObject *parent) :
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

	return Vector2(isClose ? scatterTarget() : grid()->mapFromGrid(playerCell()));
}
