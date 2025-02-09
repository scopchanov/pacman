#ifndef ENEMYORIENTATION_H
#define ENEMYORIENTATION_H

#include "AbstractOrientationBehavior.h"

class EnemyOrientation : public AbstractOrientationBehavior
{
public:
	explicit EnemyOrientation(GameObject *parent = nullptr);

private:
	void performOrientationActions() override;
};

#endif // ENEMYORIENTATION_H
