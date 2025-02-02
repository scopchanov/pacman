#include "AbstractCharacterBehavior.h"
#include "engine/Tilemap.h"

AbstractCharacterBehavior::AbstractCharacterBehavior(GameObject *parent) :
	AbstractTimedBehavior(parent),
	m_tilemap{nullptr}
{

}

Tilemap *AbstractCharacterBehavior::tilemap() const
{
	return m_tilemap;
}

void AbstractCharacterBehavior::setTilemap(Tilemap *tilemap)
{
	m_tilemap = tilemap;
}

void AbstractCharacterBehavior::performTimedActions()
{
	if (!m_tilemap)
		return;

	performCharacterActions();
}

Vector2 AbstractCharacterBehavior::currentCell() const
{
	const QSize &halfPixmapSize{0.5*QSize(72, 72)};
	qreal x{parent()->pos().x() + halfPixmapSize.width()};
	qreal y{parent()->pos().y() + halfPixmapSize.height()};

	return Vector2(m_tilemap->posToCell(QPointF(x, y)));
}
