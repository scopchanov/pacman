#include "CameraFollow.h"
#include "engine/GameObject.h"
#include "engine/GameController.h"
#include <QGraphicsView>
#include <QScrollBar>

CameraFollow::CameraFollow(GameObject *parent) :
	AbstractCharacterBehavior(parent)
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

	m_view->centerOn(parent()->pos() + QPointF(36, 36));
}
