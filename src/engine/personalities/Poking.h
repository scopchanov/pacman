#ifndef POKING_H
#define POKING_H

#include "AbstractPersonality.h"

class Grid;

class Poking : public AbstractPersonality
{
	Q_OBJECT
public:
	explicit Poking(QObject *parent = nullptr);

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
