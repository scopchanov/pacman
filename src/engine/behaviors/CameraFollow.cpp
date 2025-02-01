#include "CameraFollow.h"
#include "engine/GameObject.h"
#include <QGraphicsView>

CameraFollow::CameraFollow() :
	AbstractCharacterBehavior()
{

}

QGraphicsView *CameraFollow::view() const
{
	return m_view;
}

void CameraFollow::setView(QGraphicsView *view)
{
	m_view = view;
}

void CameraFollow::performActions()
{
	if (!m_view)
		return;

	m_view->centerOn(m_gameObject->pos() + QPointF(36, 36));
}
