#include "AbstractPersonality.h"
#include "GameObject.h"
#include "Grid.h"
#include "Vector2.h"

AbstractPersonality::AbstractPersonality(GameObject *parent) :
	_parent{parent},
	_player{nullptr},
	_grid{nullptr}
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

GameObject *AbstractPersonality::player() const
{
	return _player;
}

void AbstractPersonality::setPlayer(GameObject *player)
{
	_player = player;
}

Grid *AbstractPersonality::grid() const
{
	return _grid;
}

void AbstractPersonality::setGrid(Grid *grid)
{
	_grid = grid;
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
