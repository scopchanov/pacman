#ifndef ABSTRACTTIMEDBEHAVIOR_H
#define ABSTRACTTIMEDBEHAVIOR_H

#include "AbstractBehavior.h"

class GameClock;

class AbstractTimedBehavior : public AbstractBehavior
{
public:
	explicit AbstractTimedBehavior(AbstractGameObject *parent = nullptr);

	GameClock *clock() const;
};

#endif // ABSTRACTTIMEDBEHAVIOR_H
