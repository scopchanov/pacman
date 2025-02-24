#ifndef ENERGIZING_H
#define ENERGIZING_H

#include "AbstractBehavior.h"
#include <QList>

class Event;
class AbstractGameObject;

class Energizing : public AbstractBehavior
{
public:
	explicit Energizing(AbstractGameObject *parent = nullptr);

	void setEvent(Event *event);
	int type() const override;

private:
	void performActions() override;

	Event *_eventPlayerEnergized;
};

#endif // ENERGIZING_H
