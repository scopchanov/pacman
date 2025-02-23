#include "AbstractPersonality.h"
#include "Game.h"
#include "GameLevel.h"
#include "Grid.h"
#include "Vector2.h"
#include "objects/Player.h"

AbstractPersonality::AbstractPersonality(GameObject *parent) :
	_parent{parent}
{

}

GameObject *AbstractPersonality::parent() const
{
	return _parent;
}

void AbstractPersonality::setParent(GameObject *parent)
{
	_parent = parent;
}

Player *AbstractPersonality::player() const
{
	return Game::ref().level()->player();
}

Grid *AbstractPersonality::grid() const
{
	return Game::ref().level()->grid();
}

QPointF AbstractPersonality::scatterTarget() const
{
	return _scatterTarget;
}

void AbstractPersonality::setScatterTarget(const QPointF &point)
{
	_scatterTarget = point;
}

Vector2 AbstractPersonality::playerCell() const
{
	return Vector2(grid()->mapToGrid(player()->pos()));
}
