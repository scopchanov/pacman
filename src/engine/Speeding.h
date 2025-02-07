#ifndef SPEEDING_H
#define SPEEDING_H

#include "AbstractChasingStrategy.h"

class Grid;

class Speeding : public AbstractChasingStrategy
{
public:
	explicit Speeding();

	Grid *grid() const;
	void setGrid(Grid *grid);

	Vector2 calculateTargetPosition() const override;

private:
	Grid *_grid;
};

#endif // SPEEDING_H
