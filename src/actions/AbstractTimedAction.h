#ifndef ABSTRACTTIMEDACTION_H
#define ABSTRACTTIMEDACTION_H

#include "AbstractAction.h"

class Clock;

class AbstractTimedAction : public AbstractAction
{
public:
	explicit AbstractTimedAction(AbstractComponent *parent = nullptr);

protected:
	Clock *clock() const;
};

#endif // ABSTRACTTIMEDACTION_H
