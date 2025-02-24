#ifndef DOTSEATING_H
#define DOTSEATING_H

#include "AbstractSpatialBehavior.h"
#include <QList>

class Event;

class DotsEating : public AbstractSpatialBehavior
{
public:
	enum EventType : int {
		ET_DotEaten = 0,
		ET_PlayerWins
	};

	explicit DotsEating(AbstractGameObject *parent = nullptr);
	
	void setEvent(EventType type, Event *event);
	int type() const override;

private:
	void performSpatialActions() override;
	void triggerEvent(EventType type);

	QList<Event *> _events;
};

#endif // DOTSEATING_H
