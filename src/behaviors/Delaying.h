#ifndef DELAYING_H
#define DELAYING_H

#include "AbstractTimedBehavior.h"

class Event;

class Delaying : public AbstractTimedBehavior
{
public:
	explicit Delaying(AbstractGameObject *parent = nullptr);

	qreal duration() const;
	void setDuration(qreal duration);
	void addAction(AbstractAction *action);
	void setEventTick(Event *event);
	int type() const override;

	void reset() override;

private:
	void performActions() override;
	bool increaseTime();
	void triggerTickEvent();
	bool delayDurationExceeded() const;

	qreal _duration;
	qreal _time;
	Event *_eventTick;
	QList<AbstractAction *> _actions;
};

#endif // DELAYING_H
