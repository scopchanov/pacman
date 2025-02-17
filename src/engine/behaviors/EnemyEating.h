#ifndef ENEMYEATING_H
#define ENEMYEATING_H

#include "AbstractBehavior.h"

class Enemy;
class GameEvent;
class GameObject;

class EnemyEating : public AbstractBehavior
{
public:
	explicit EnemyEating(GameObject *parent = nullptr);

	void setEvent(GameEvent *event);
	int type() const override;

	void reset() override;

private:
	void performActions() override;
	void eatEnemy(Enemy *enemy);
	int points() const;

	int _enemiesEaten;
	GameEvent *_eventEnemyEaten;
};

#endif // ENEMYEATING_H
