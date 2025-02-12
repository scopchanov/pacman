#ifndef ENEMYEATING_H
#define ENEMYEATING_H

#include "AbstractBehavior.h"

class EnemyEating : public AbstractBehavior
{
public:
	explicit EnemyEating(GameObject *parent = nullptr);

	int type() const override;

private:
	void performActions() override;
};

#endif // ENEMYEATING_H
