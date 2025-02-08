#ifndef DOTSEATING_H
#define DOTSEATING_H

#include "AbstractSpatialBehavior.h"
#include <QList>

class GameEvent;

class DotsEating : public AbstractSpatialBehavior
{
public:
	enum EventType : int {
		ET_DotEaten = 0,
		ET_PlayerWins
	};

	explicit DotsEating(GameObject *parent = nullptr);

	void setEvent(EventType type, GameEvent *event);
	int type() const override;

	void reset() override;

private:
	void performSpatialActions() override;
	void triggerGameEvent(EventType type);

	QList<GameEvent *> m_gameEvents;
};

#endif // DOTSEATING_H
