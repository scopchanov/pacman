#ifndef ABSTRACTTIMEDBEHAVIOR_H
#define ABSTRACTTIMEDBEHAVIOR_H

#include "AbstractAction.h"

class Clock;

class AbstractTimedBehavior : public AbstractAction
{
public:
	explicit AbstractTimedBehavior(AbstractComponent *parent = nullptr);

	Clock *clock() const;
};

#endif // ABSTRACTTIMEDBEHAVIOR_H
