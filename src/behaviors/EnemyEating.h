#ifndef ENEMYEATING_H
#define ENEMYEATING_H

#include "AbstractBehavior.h"

class Enemy;
class Event;
class AbstractGameObject;

class EnemyEating : public AbstractBehavior
{
public:
	explicit EnemyEating(AbstractComponent *parent = nullptr);

	void setEvent(Event *event);
	int type() const override;

	void reset() override;

protected:
	void performTasks() override;

private:
	void eatEnemy(Enemy *enemy);
	int points() const;

	int _enemiesEaten;
	Event *_eventEnemyEaten;
};

#endif // ENEMYEATING_H
