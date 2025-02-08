#ifndef ENEMYORIENTATION_H
#define ENEMYORIENTATION_H

#include "AbstractBehavior.h"
#include <QtGlobal>

class CharacterMovement;
class Vector2;

class EnemyOrientation : public AbstractBehavior
{
public:
	explicit EnemyOrientation(GameObject *parent = nullptr);

	void setMovement(CharacterMovement *movement);
	int type() const override;

	void reset() override;

private:
	void performActions() override;

	CharacterMovement *_movement;
};

#endif // ENEMYORIENTATION_H
