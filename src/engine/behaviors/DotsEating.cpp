#include "DotsEating.h"
#include "engine/GameController.h"
#include "engine/Tilemap.h"
#include <QPointF>

DotsEating::DotsEating() :
	AbstractCharacterBehavior()
{

}

void DotsEating::performActions()
{
	eatDotIfAvailable();
}

void DotsEating::eatDotIfAvailable()
{
	const QPoint &cell{currentCell().toPoint()};
	int row{cell.y()};
	int column{cell.x()};

	if (!m_tilemap->hasTile(row, column))
		return;

	m_tilemap->resetTile(row, column);

	if (m_tilemap->tileCount())
		return;

	m_gameController->stop();

	qDebug() << "You win!";
}
