#ifndef DELAYING_H
#define DELAYING_H

#include "AbstractBehavior.h"

class Delaying : public AbstractBehavior
{
	Q_OBJECT
public:
	explicit Delaying(AbstractComponent *parent = nullptr);

	qreal duration() const;
	void setDuration(qreal duration);
	qreal time() const;
	int type() const override;

	void reset() override;

protected:
	void performTasks() override;

private:
	bool increaseTime();
	bool delayDurationExceeded() const;

	qreal _duration;
	qreal _time;
};

#endif // DELAYING_H
