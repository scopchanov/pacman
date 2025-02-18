#include "AbstractSpatialBehavior.h"
#include "engine/Grid.h"
#include "engine/Tilemap.h"
#include "engine/objects/GameObject.h"

AbstractSpatialBehavior::AbstractSpatialBehavior(GameObject *parent) :
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
