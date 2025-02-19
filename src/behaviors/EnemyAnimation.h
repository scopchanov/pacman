#ifndef ENEMYANIMATION_H
#define ENEMYANIMATION_H

#include "AbstractAnimationBehavior.h"

class EnemyAnimation : public AbstractAnimationBehavior
{
public:
	explicit EnemyAnimation(GameObject *parent = nullptr);

private:
	void update() override;
};

#endif // ENEMYANIMATION_H
