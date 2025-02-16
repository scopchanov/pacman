#ifndef LIFETIMELIMITING_H
#define LIFETIMELIMITING_H

#include "AbstractTimedBehavior.h"

class LifetimeLimiting : public AbstractTimedBehavior
{
public:
	explicit LifetimeLimiting(GameObject *parent = nullptr);

	qreal duration() const;
	void setDuration(qreal duration);
	int type() const override;

	void reset() override;

private:
	void performTimedActions() override;
	void deleteGameObject();

	qreal _duration;
	qreal _time;
};

#endif // LIFETIMELIMITING_H
