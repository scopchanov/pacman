#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "AbstractBehavior.h"

class CharacterMovement;

class EnemyController : public AbstractBehavior
{
public:
	explicit EnemyController(GameObject *parent = nullptr);

	void setCharacterMovement(CharacterMovement *characterMovement);
	int type() const override;

private:
	void performActions() override;

	CharacterMovement *m_characterMovement;
};

#endif // ENEMYCONTROLLER_H
