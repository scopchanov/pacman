#ifndef EYEORIENTATE_H
#define EYEORIENTATE_H

#include "AbstractOrientate.h"

class EnemyEye;
class Vector2;

class EyeOrientate : public AbstractOrientate
{
public:
	explicit EyeOrientate(AbstractComponent *parent = nullptr);

	void reset() override;

private:
	void orientate() override;
	Vector2 currentDirection();
	EnemyEye *enemyEye() const;
};

#endif // EYEORIENTATE_H
