#ifndef ABSTRACTTIMEDBEHAVIOR_H
#define ABSTRACTTIMEDBEHAVIOR_H

#include "AbstractBehavior.h"

class Clock;

class AbstractTimedBehavior : public AbstractBehavior
{
public:
	explicit AbstractTimedBehavior(AbstractGameObject *parent = nullptr);

	Clock *clock() const;
};

#endif // ABSTRACTTIMEDBEHAVIOR_H
