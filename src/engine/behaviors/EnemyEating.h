#ifndef ENEMYEATING_H
#define ENEMYEATING_H

#include "AbstractBehavior.h"

class EnemyEating : public AbstractBehavior
{
public:
	explicit EnemyEating(GameObject *parent = nullptr);

	int type() const override;

	void reset() override;

private:
	void performActions() override;
	int points() const;

	int _enemiesEaten;
};

#endif // ENEMYEATING_H
