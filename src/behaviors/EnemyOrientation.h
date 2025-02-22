#ifndef ENEMYORIENTATION_H
#define ENEMYORIENTATION_H

#include "AbstractOrientationBehavior.h"

class GhostEye;

class EnemyOrientation : public AbstractOrientationBehavior
{
public:
	explicit EnemyOrientation(GameObject *parent = nullptr);

	void reset() override;

private:
	void performOrientationActions() override;
	GhostEye *ghostEye(int n) const;
};

#endif // ENEMYORIENTATION_H
