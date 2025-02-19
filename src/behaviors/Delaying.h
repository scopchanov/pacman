#ifndef DELAYING_H
#define DELAYING_H

#include "AbstractTimedBehavior.h"

class Delaying : public AbstractTimedBehavior
{
public:
	explicit Delaying(GameObject *parent = nullptr);

	qreal duration() const;
	void setDuration(qreal duration);
	void addAction(AbstractAction *action);
	int type() const override;

	void reset() override;

private:
	void performActions() override;
	bool increaseTime();
	bool delayDurationExceeded() const;

	qreal _duration;
	qreal _time;
	QList<AbstractAction *> _actions;
};

#endif // DELAYING_H
