#include "AbstractCharacterBehavior.h"
#include "engine/Tilemap.h"

AbstractCharacterBehavior::AbstractCharacterBehavior(GameObject *parent) :
	AbstractBehavior(parent),
	m_gameController{nullptr},
	m_tilemap{nullptr}
{

}

GameController *AbstractCharacterBehavior::gameController() const
{
	return m_gameController;
}

void AbstractCharacterBehavior::setGameController(GameController *gameController)
{
	m_gameController = gameController;
}

Tilemap *AbstractCharacterBehavior::tilemap() const
{
	return m_tilemap;
}

void AbstractCharacterBehavior::setTilemap(Tilemap *tilemap)
{
	m_tilemap = tilemap;
}

void AbstractCharacterBehavior::execute()
{
	if (!parent() || !m_gameController || !m_tilemap)
		return;

	performActions();
}

Vector2 AbstractCharacterBehavior::currentCell() const
{
	const QSize &halfPixmapSize{0.5*QSize(72, 72)};
	qreal x{parent()->pos().x() + halfPixmapSize.width()};
	qreal y{parent()->pos().y() + halfPixmapSize.height()};

	return Vector2(m_tilemap->posToCell(QPointF(x, y)));
}
