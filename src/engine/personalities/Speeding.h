#ifndef SPEEDING_H
#define SPEEDING_H

#include "AbstractPersonality.h"

class Grid;

class Speeding : public AbstractPersonality
{
	Q_OBJECT
public:
	explicit Speeding(QObject *parent = nullptr);

	Grid *grid() const;
	void setGrid(Grid *grid);

	Vector2 calculateTargetPosition() const override;

private:
	Grid *_grid;
};

#endif // SPEEDING_H
