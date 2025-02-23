#ifndef ENEMYANIMATING_H
#define ENEMYANIMATING_H

#include "AbstractAnimatingBehavior.h"

class EnemyAnimating : public AbstractAnimatingBehavior
{
public:
	explicit EnemyAnimating(GameObject *parent = nullptr);

private:
	void update() override;
};

#endif // ENEMYANIMATING_H
