#ifndef ABSTRACTTIMEDBEHAVIOR_H
#define ABSTRACTTIMEDBEHAVIOR_H

#include "AbstractBehavior.h"

class GameTimer;

class AbstractTimedBehavior : public AbstractBehavior
{
public:
	AbstractTimedBehavior(GameObject *parent = nullptr);

	GameTimer *gameTimer() const;
	virtual void setGameTimer(GameTimer *gameTimer);

private:
	void performActions() override final;
	virtual void performTimedActions() = 0;

	GameTimer *m_gameTimer;
};

#endif // ABSTRACTTIMEDBEHAVIOR_H
