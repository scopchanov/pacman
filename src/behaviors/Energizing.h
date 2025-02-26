#ifndef ENERGIZING_H
#define ENERGIZING_H

#include "AbstractBehavior.h"
#include <QList>

class Event;
class AbstractGameObject;

class Energizing : public AbstractBehavior
{
public:
	explicit Energizing(AbstractComponent *parent = nullptr);

	void setEvent(Event *event);
	int type() const override;

protected:
	void performTasks() override;

private:
	Event *_eventPlayerEnergized;
};

#endif // ENERGIZING_H
