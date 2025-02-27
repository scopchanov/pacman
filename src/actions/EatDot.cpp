#include "EatDot.h"
#include "AbstractGameObject.h"
#include "GameGlobals.h"
#include "Grid.h"
#include "Tilemap.h"
#include "Vector2.h"
#include <QPointF>

EatDot::EatDot(AbstractComponent *parent) :
	AbstractAction(parent),
	_tilemap{nullptr}
{

}

Tilemap *EatDot::tilemap() const
{
	return _tilemap;
}

void EatDot::setTilemap(Tilemap *tilemap)
{
	_tilemap = tilemap;
}

int EatDot::type() const
{
	return ACT_EatDot;
}

void EatDot::performTasks()
{
	const QPoint &cell{currentCell().toPoint()};
	int row{cell.y()};
	int column{cell.x()};

	if (!tilemap()->hasTile(row, column))
		return;

	tilemap()->resetTile(row, column);

	emit dotEaten();

	if (tilemap()->tileCount())
		return;

	emit playerWon();
}

Vector2 EatDot::currentCell() const
{
	return Vector2(_tilemap->grid()->mapToGrid(gameObject()->pos()));
}
