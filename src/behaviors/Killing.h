#ifndef KILLING_H
#define KILLING_H

#include "AbstractTimedBehavior.h"

class GameEvent;

class Killing : public AbstractTimedBehavior
{
public:
	explicit Killing(AbstractGameObject *parent = nullptr);

	void setEventPlayerDies(GameEvent *gameEvent);
	int type() const override;

private:
	void performActions() override;

	GameEvent *_eventPlayerDies;
};

#endif // KILLING_H
