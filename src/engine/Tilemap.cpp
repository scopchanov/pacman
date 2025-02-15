#include "Tilemap.h"
#include "Grid.h"
#include "Tile.h"
#include "Vector2.h"
#include <QGraphicsScene>

Tilemap::Tilemap(GameObject *parent) :
	GameObject(parent),
	_grid{nullptr},
	_tileCount{0}
{

}

Grid *Tilemap::grid() const
{
	return _grid;
}

void Tilemap::setGrid(Grid *grid)
{
	_grid = grid;

	if (!_grid)
		return;

	QList<Tile *> row;

	row.fill(nullptr, _grid->columnCount());

	_tiles.fill(row, _grid->rowCount());
}

int Tilemap::tileCount() const
{
	return _tileCount;
}

bool Tilemap::setTile(int row, int col, Tile *tile)
{
	if (!_grid || row < 0 || row >= _grid->rowCount()
		|| col < 0 || col >= _grid->columnCount())
		return false;

	auto *oldTile = _tiles.at(row).at(col);

	if (oldTile) {
		deleteTile(oldTile);
		addTile(row, col, tile);
	} else {
		addTile(row, col, tile);
	}

	_tiles[row][col] = tile;

	return true;
}

bool Tilemap::resetTile(int row, int col)
{
	return setTile(row, col, nullptr);
}

bool Tilemap::hasTile(int row, int col) const
{
	return _tiles.at(row).at(col);
}

bool Tilemap::hasTile(const Vector2 &cell) const
{
	return hasTile(cell.y(), cell.x());
}

void Tilemap::clear()
{
	for (int m{0}; m < _grid->rowCount(); m++)
		for (int n{0}; n < _grid->columnCount(); n++)
			setTile(m, n, nullptr);
}

void Tilemap::deleteTile(Tile *tile)
{
	if (tile->scene())
		tile->scene()->removeItem(tile);

	delete tile;

	_tileCount--;
}

void Tilemap::addTile(int row, int col, Tile *tile)
{
	if (!_grid || !tile)
		return;

	const QSizeF &cellSize{_grid->cellSize()};

	tile->setParentItem(this);
	tile->setPos((col + 0.5)*cellSize.width(), (row + 0.5)*cellSize.height());

	_tileCount++;
}
