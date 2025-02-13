#ifndef ABSTRACTTIMEDBEHAVIOR_H
#define ABSTRACTTIMEDBEHAVIOR_H

#include "AbstractBehavior.h"

class GameClock;

class AbstractTimedBehavior : public AbstractBehavior
{
public:
	explicit AbstractTimedBehavior(GameObject *parent = nullptr);

	GameClock *gameClock() const;
	virtual void setGameClock(GameClock *gameTimer);

private:
	void performActions() override final;
	virtual void performTimedActions() = 0;

	GameClock *_gameTimer;
};

#endif // ABSTRACTTIMEDBEHAVIOR_H
