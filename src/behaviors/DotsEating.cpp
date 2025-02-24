#include "DotsEating.h"
#include "Event.h"
#include "GameGlobals.h"
#include "Tilemap.h"
#include <QPointF>

DotsEating::DotsEating(AbstractGameObject *parent) :
	AbstractSpatialBehavior(parent)
{
	for (int n{0}; n < 2; n++)
		_events.append(nullptr);
}

void DotsEating::setEvent(EventType type, Event *event)
{
	_events[type] = event;
}

int DotsEating::type() const
{
	return BT_DotsEating;
}

void DotsEating::performSpatialActions()
{
	const QPoint &cell{currentCell().toPoint()};
	int row{cell.y()};
	int column{cell.x()};

	if (!tilemap()->hasTile(row, column))
		return;

	tilemap()->resetTile(row, column);
	triggerEvent(ET_DotEaten);

	if (tilemap()->tileCount())
		return;

	triggerEvent(ET_PlayerWins);
}

void DotsEating::triggerEvent(EventType type)
{
	auto *event{_events.at(type)};

	if (!event)
		return;

	event->trigger();
}
