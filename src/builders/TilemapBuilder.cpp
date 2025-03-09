#include "TilemapBuilder.h"
#include "PathBuilder.h"
#include "Tilemap.h"
// #include "Grid.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

TilemapBuilder::TilemapBuilder(QObject *parent) :
	QObject{parent},
	_tilemap{nullptr},
	_grid{nullptr}
{

}

Tilemap *TilemapBuilder::tilemap() const
{
	return _tilemap;
}

void TilemapBuilder::setTilemap(Tilemap *tilemap)
{
	_tilemap = tilemap;
}

Grid *TilemapBuilder::grid() const
{
	return _grid;
}

void TilemapBuilder::setGrid(Grid *grid)
{
	_grid = grid;
}

QPen TilemapBuilder::pen() const
{
	return _pen;
}

void TilemapBuilder::setPen(const QPen &pen)
{
	_pen = pen;
}

QBrush TilemapBuilder::brush() const
{
	return _brush;
}

void TilemapBuilder::setBrush(const QBrush &brush)
{
	_brush = brush;
}

void TilemapBuilder::build(const QJsonArray &matrix)
{
	if (!_tilemap || !_grid)
		return;

	_tilemap->setGrid(_grid);

	for (const auto &element : matrix) {
		const QJsonObject &json{element.toObject()};
		int row{json.value("row").toInt()};
		int col{json.value("col").toInt()};
		int pathIndex{json.value("index").toInt()};

		setTile(row, col, pathIndex);
	}
}

void TilemapBuilder::setTile(int row, int col, int pathIndex)
{
	if (!_tilemap)
		return;

	_tilemap->setTile(row, col, createTile(pathIndex));
}

QGraphicsItem *TilemapBuilder::createTile(int pathIndex)
{
	auto *tile{new QGraphicsPathItem()};
	auto tilePathIndex{static_cast<PathBuilder::TileType>(pathIndex)};

	tile->setPath(PathBuilder::tilePath(tilePathIndex));
	tile->setPen(_pen);
	tile->setBrush(_brush);

	return tile;
}
