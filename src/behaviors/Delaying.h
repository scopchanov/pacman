#ifndef DELAYING_H
#define DELAYING_H

#include "AbstractTimedBehavior.h"

class Event;

class Delaying : public AbstractTimedBehavior
{
public:
	explicit Delaying(AbstractComponent *parent = nullptr);

	qreal duration() const;
	void setDuration(qreal duration);
	void setEventTick(Event *event);
	int type() const override;

	void reset() override;

protected:
	void performTasks() override;

private:
	bool increaseTime();
	void triggerTickEvent();
	bool delayDurationExceeded() const;

	qreal _duration;
	qreal _time;
	Event *_eventTick;
};

#endif // DELAYING_H
