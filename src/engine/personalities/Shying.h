#ifndef SHYING_H
#define SHYING_H

#include "AbstractPersonality.h"

class Grid;

class Shying : public AbstractPersonality
{
	Q_OBJECT
public:
	explicit Shying(QObject *parent = nullptr);

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
