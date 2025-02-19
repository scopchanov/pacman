#ifndef KILLPLAYER_H
#define KILLPLAYER_H

#include "AbstractTimedBehavior.h"

class GameEvent;

class KillPlayer : public AbstractTimedBehavior
{
public:
	explicit KillPlayer(GameObject *parent = nullptr);

	void setEventPlayerDies(GameEvent *gameEvent);
	int type() const override;

private:
	void performActions() override;

	GameEvent *_eventPlayerDies;
};

#endif // KILLPLAYER_H
