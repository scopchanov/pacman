#ifndef POWERINGUP_H
#define POWERINGUP_H

#include "AbstractBehavior.h"
#include <QList>

class GameObject;

class PoweringUp : public AbstractBehavior
{
public:
	explicit PoweringUp(GameObject *parent = nullptr);

	GameObject *player() const;
	void setPlayer(GameObject *player);
	void addEnemy(GameObject *enemy);
	int type() const override;

private:
	void performActions() override;

	GameObject *_player;
	QList<GameObject *> _enemies;
};

#endif // POWERINGUP_H
