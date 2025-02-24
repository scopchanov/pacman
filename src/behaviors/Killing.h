#ifndef KILLING_H
#define KILLING_H

#include "AbstractTimedBehavior.h"

class Event;

class Killing : public AbstractTimedBehavior
{
public:
	explicit Killing(AbstractGameObject *parent = nullptr);

	void setEventPlayerDies(Event *event);
	int type() const override;

private:
	void performActions() override;

	Event *_eventPlayerDies;
};

#endif // KILLING_H
