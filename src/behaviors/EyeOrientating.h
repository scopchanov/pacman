#ifndef EYEORIENTATING_H
#define EYEORIENTATING_H

#include "AbstractOrientatingBehavior.h"

class EnemyEye;
class Vector2;

class EyeOrientating : public AbstractOrientatingBehavior
{
public:
	explicit EyeOrientating(AbstractComponent *parent = nullptr);

	void reset() override;

private:
	void performOrientationActions() override;
	Vector2 currentDirection();
	EnemyEye *enemyEye() const;
};

#endif // EYEORIENTATING_H
