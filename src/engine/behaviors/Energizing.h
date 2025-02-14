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

	GameObject *player() const;
	void setPlayer(GameObject *player);
	void addEnemy(GameObject *enemy);
	void setEvent(GameEvent *event);
	int type() const override;

private:
	void performActions() override;

	GameObject *_player;
	QList<GameObject *> _enemies;
	GameEvent *_eventPlayerEnergized;
};

#endif // ENERGIZING_H
