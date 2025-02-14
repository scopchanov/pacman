#ifndef ENERGIZING_H
#define ENERGIZING_H

#include "AbstractBehavior.h"
#include <QList>

class GameObject;

class Energizing : public AbstractBehavior
{
public:
	explicit Energizing(GameObject *parent = nullptr);

	GameObject *player() const;
	void setPlayer(GameObject *player);
	void addEnemy(GameObject *enemy);
	int type() const override;

private:
	void performActions() override;

	GameObject *_player;
	QList<GameObject *> _enemies;
};

#endif // ENERGIZING_H
