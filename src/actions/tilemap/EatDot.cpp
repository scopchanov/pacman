#include "EatDot.h"
#include "AbstractGameObject.h"
#include "Game.h"
#include "GameGlobals.h"
#include "Grid.h"
#include "GameLevel.h"
#include "Tilemap.h"
#include "Vector2.h"
#include <QPointF>

EatDot::EatDot(AbstractComponent *parent) :
	AbstractTilemapAction(parent)
{

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
	Tilemap *dots{tilemap()};

	if (!dots->hasTile(row, column))
		return;

	dots->resetTile(row, column);

	emit dotEaten();

	if (dots->tileCount())
		return;

	emit playerWon();
}

Tilemap *EatDot::tilemap() const
{
	return Game::ref().level()->dots();
}

