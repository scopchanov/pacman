#ifndef ABSTRACTTIMEDBEHAVIOR_H
#define ABSTRACTTIMEDBEHAVIOR_H

#include "AbstractBehavior.h"

class GameClock;

class AbstractTimedBehavior : public AbstractBehavior
{
public:
	explicit AbstractTimedBehavior(GameObject *parent = nullptr);

	GameClock *clock() const;
	virtual void setClock(GameClock *clock);

private:
	void performActions() override final;
	virtual void performTimedActions() = 0;

	GameClock *_clock;
};

#endif // ABSTRACTTIMEDBEHAVIOR_H
