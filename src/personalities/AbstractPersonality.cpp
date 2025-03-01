#include "AbstractPersonality.h"
#include "Game.h"
#include "GameLevel.h"
#include "Grid.h"
#include "Vector2.h"
#include "objects/Player.h"

AbstractPersonality::AbstractPersonality(AbstractGameObject *parent) :
	_parent{parent}
{

}

AbstractGameObject *AbstractPersonality::parent() const
{
	return _parent;
}

void AbstractPersonality::setParent(AbstractGameObject *parent)
{
	_parent = parent;
}

int AbstractPersonality::colorRole() const
{
	return _colorRole;
}

void AbstractPersonality::setColorRole(int role)
{
	_colorRole = role;
}

QPointF AbstractPersonality::scatterTarget() const
{
	return _scatterTarget;
}

void AbstractPersonality::setScatterTarget(const QPointF &point)
{
	_scatterTarget = point;
}

Player *AbstractPersonality::player() const
{
	return Game::ref().level()->player();
}

Grid *AbstractPersonality::grid() const
{
	return Game::ref().level()->grid();
}

Vector2 AbstractPersonality::playerCell() const
{
	return Vector2(grid()->mapToGrid(player()->pos()));
}
