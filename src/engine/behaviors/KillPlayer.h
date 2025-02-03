#ifndef KILLPLAYER_H
#define KILLPLAYER_H

#include "AbstractTimedBehavior.h"

class QSoundEffect;

class KillPlayer : public AbstractTimedBehavior
{
public:
	explicit KillPlayer(GameObject *parent = nullptr);
	~KillPlayer();

	GameObject *player() const;
	void setPlayer(GameObject *player);

	int type() const override;

private:
	void performTimedActions() override;

	GameObject *m_player;
	QSoundEffect *m_effectDied;
};

#endif // KILLPLAYER_H
