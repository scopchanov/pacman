#include "AbstractSpatialBehavior.h"
#include "engine/Tilemap.h"
#include "engine/Grid.h"

AbstractSpatialBehavior::AbstractSpatialBehavior(GameObject *parent) :
	AbstractTimedBehavior(parent),
	m_tilemap{nullptr}
{

}

Tilemap *AbstractSpatialBehavior::tilemap() const
{
	return m_tilemap;
}

void AbstractSpatialBehavior::setTilemap(Tilemap *tilemap)
{
	m_tilemap = tilemap;
}

void AbstractSpatialBehavior::performTimedActions()
{
	if (!m_tilemap)
		return;

	performSpatialActions();
}

Vector2 AbstractSpatialBehavior::currentCell() const
{
	return Vector2(m_tilemap->grid()->posToCell(parent()->pos()));
}
