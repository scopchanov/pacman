#ifndef POKING_H
#define POKING_H

#include "AbstractChasingStrategy.h"

class Grid;

class Poking : public AbstractChasingStrategy
{
public:
	explicit Poking();

	GameObject *enemy() const;
	void setEnemy(GameObject *enemy);
	Grid *grid() const;
	void setGrid(Grid *grid);

	Vector2 calculateTargetPosition() const override;

private:
	GameObject *_enemy;
	Grid *_grid;
};

#endif // POKING_H
