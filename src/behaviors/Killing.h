#ifndef KILLING_H
#define KILLING_H

#include "AbstractTimedBehavior.h"

class Event;

class Killing : public AbstractTimedBehavior
{
public:
	explicit Killing(AbstractComponent *parent = nullptr);

	void setEventPlayerDied(Event *event);
	int type() const override;

protected:
	void performTasks() override;

private:
	Event *_eventPlayerDied;
};

#endif // KILLING_H
