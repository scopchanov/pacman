#ifndef ENEMYANIMATION_H
#define ENEMYANIMATION_H

#include "AbstractAnimationBehavior.h"

class EnemyAnimation : public AbstractAnimationBehavior
{
public:
	explicit EnemyAnimation(GameObject *parent = nullptr);

	void reset() override;

private:
	void foo() override;
	void updateParent() override;
};

#endif // ENEMYANIMATION_H
