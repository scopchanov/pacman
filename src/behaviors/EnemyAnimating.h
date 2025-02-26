#ifndef ENEMYANIMATING_H
#define ENEMYANIMATING_H

#include "AbstractAnimatingBehavior.h"

class EnemyAnimating : public AbstractAnimatingBehavior
{
public:
	explicit EnemyAnimating(AbstractComponent *parent = nullptr);

	void reset() override;

private:
	void update() override;
};

#endif // ENEMYANIMATING_H
