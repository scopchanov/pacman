#ifndef FRIGHTENENEMIES_H
#define FRIGHTENENEMIES_H

#include "AbstractAction.h"

class Enemy;
class EnemyController;
class CharacterMovement;

class FrightenEnemies : public AbstractAction
{
public:
	explicit FrightenEnemies(AbstractBehavior *parent = nullptr);

	int type() const override;

private:
	void performTask() override;
	EnemyController *controller(Enemy *enemy) const;
	CharacterMovement *movement(Enemy *enemy) const;
};

#endif // FRIGHTENENEMIES_H
