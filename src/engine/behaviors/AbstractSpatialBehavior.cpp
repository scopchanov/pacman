#include "AbstractSpatialBehavior.h"
#include "engine/Tilemap.h"

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
	const QSize &halfPixmapSize{0.5*QSize(72, 72)};
	qreal x{parent()->pos().x() + halfPixmapSize.width()};
	qreal y{parent()->pos().y() + halfPixmapSize.height()};

	return Vector2(m_tilemap->posToCell(QPointF(x, y)));
}
