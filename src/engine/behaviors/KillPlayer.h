#ifndef KILLPLAYER_H
#define KILLPLAYER_H

#include "AbstractTimedBehavior.h"

class GameEvent;

class KillPlayer : public AbstractTimedBehavior
{
public:
	explicit KillPlayer(GameObject *parent = nullptr);

	GameObject *player() const;
	void setPlayer(GameObject *player);
	void setEventPlayerDies(GameEvent *gameEvent);
	int type() const override;

	void reset() override;

private:
	void performTimedActions() override;

	GameObject *m_player;
	GameEvent *m_eventPlayerDies;
};

#endif // KILLPLAYER_H
