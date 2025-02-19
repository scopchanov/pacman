#include "CameraFollow.h"
#include "GameGlobals.h"
#include "GameObject.h"
#include <QGraphicsView>
#include <QScrollBar>

CameraFollow::CameraFollow(GameObject *parent) :
	AbstractBehavior(parent)
{

}

QGraphicsView *CameraFollow::view() const
{
	return _view;
}

void CameraFollow::setView(QGraphicsView *view)
{
	_view = view;
}

int CameraFollow::type() const
{
	return BT_CameraFollow;
}

void CameraFollow::performActions()
{
	if (!_view)
		return;

	_view->centerOn(parent()->pos());
}
