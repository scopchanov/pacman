#include "DotsEating.h"
#include "engine/GameEvent.h"
#include "engine/Tilemap.h"
#include <QPointF>

DotsEating::DotsEating(GameObject *parent) :
	AbstractSpatialBehavior(parent)
{
	for (int n{0}; n < 2; n++)
		m_gameEvents.append(nullptr);
}

void DotsEating::setEvent(EventType type, GameEvent *event)
{
	m_gameEvents[type] = event;
}

int DotsEating::type() const
{
	return BT_DotsEating;
}

void DotsEating::reset()
{

}

void DotsEating::performSpatialActions()
{
	const QPoint &cell{currentCell().toPoint()};
	int row{cell.y()};
	int column{cell.x()};

	if (!tilemap()->hasTile(row, column))
		return;

	tilemap()->resetTile(row, column);
	triggerGameEvent(ET_DotEaten);

	if (tilemap()->tileCount())
		return;

	triggerGameEvent(ET_PlayerWins);
}

void DotsEating::triggerGameEvent(EventType type)
{
	auto *gameEvent{m_gameEvents.at(type)};

	if (!gameEvent)
		return;

	gameEvent->trigger();
}
