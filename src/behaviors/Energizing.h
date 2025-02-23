#ifndef ENERGIZING_H
#define ENERGIZING_H

#include "AbstractBehavior.h"
#include <QList>

class GameEvent;
class GameObject;

class Energizing : public AbstractBehavior
{
public:
	explicit Energizing(GameObject *parent = nullptr);

	void setEvent(GameEvent *event);
	int type() const override;

private:
	void performActions() override;

	GameEvent *_eventPlayerEnergized;
};

#endif // ENERGIZING_H
