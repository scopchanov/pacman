#include "AbstractSpatialBehavior.h"
#include "Grid.h"
#include "Tilemap.h"
#include "AbstractGameObject.h"

AbstractSpatialBehavior::AbstractSpatialBehavior(AbstractGameObject *parent) :
	AbstractTimedBehavior(parent),
	_tilemap{nullptr}
{

}

Tilemap *AbstractSpatialBehavior::tilemap() const
{
	return _tilemap;
}

void AbstractSpatialBehavior::setTilemap(Tilemap *tilemap)
{
	_tilemap = tilemap;
}

void AbstractSpatialBehavior::performActions()
{
	if (!_tilemap)
		return;

	performSpatialActions();
}

Vector2 AbstractSpatialBehavior::currentCell() const
{
	return Vector2(_tilemap->grid()->mapToGrid(parent()->pos()));
}
