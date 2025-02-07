#ifndef SHYING_H
#define SHYING_H

#include "AbstractChasingStrategy.h"

class Grid;

class Shying : public AbstractChasingStrategy
{
public:
	explicit Shying();

	Grid *grid() const;
	void setGrid(Grid *grid);
	GameObject *enemy() const;
	void setEnemy(GameObject *enemy);

	Vector2 calculateTargetPosition() const override;

private:
	Grid *_grid;
	GameObject *_enemy;
};

#endif // SHYING_H
