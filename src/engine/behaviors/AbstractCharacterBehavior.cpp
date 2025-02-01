#include "AbstractCharacterBehavior.h"
#include "engine/Tilemap.h"

AbstractCharacterBehavior::AbstractCharacterBehavior() :
	AbstractBehavior(),
	m_gameObject{nullptr},
	m_gameController{nullptr},
	m_tilemap{nullptr}
{

}

void AbstractCharacterBehavior::setGameObject(GameObject *gameObject)
{
	m_gameObject = gameObject;
}

void AbstractCharacterBehavior::setGameController(GameController *gameController)
{
	m_gameController = gameController;
}

void AbstractCharacterBehavior::setTilemap(Tilemap *tilemap)
{
	m_tilemap = tilemap;
}

void AbstractCharacterBehavior::execute()
{
	if (!m_gameObject || !m_gameController || !m_tilemap)
		return;

	performActions();
}

Vector2 AbstractCharacterBehavior::currentCell() const
{
	const QSize &halfPixmapSize{0.5*QSize(72, 72)};
	qreal x{m_gameObject->pos().x() + halfPixmapSize.width()};
	qreal y{m_gameObject->pos().y() + halfPixmapSize.height()};

	return Vector2(m_tilemap->posToCell(QPointF(x, y)));
}
