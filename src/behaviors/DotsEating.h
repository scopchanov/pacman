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

	explicit DotsEating(AbstractGameObject *parent = nullptr);

	void setEvent(EventType type, GameEvent *event);
	int type() const override;

private:
	void performSpatialActions() override;
	void triggerGameEvent(EventType type);

	QList<GameEvent *> _gameEvents;
};

#endif // DOTSEATING_H
