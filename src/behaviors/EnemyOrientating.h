#ifndef ENEMYORIENTATING_H
#define ENEMYORIENTATING_H

#include "AbstractOrientatingBehavior.h"

class GhostEye;

class EnemyOrientating : public AbstractOrientatingBehavior
{
public:
	explicit EnemyOrientating(AbstractGameObject *parent = nullptr);

	void reset() override;

private:
	void performOrientationActions() override;
	GhostEye *ghostEye(int n) const;
};

#endif // ENEMYORIENTATING_H
