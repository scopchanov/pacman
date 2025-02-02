#include "Tilemap.h"
#include "Grid.h"
#include "Tile.h"

Tilemap::Tilemap(QGraphicsItem *parent) :
	GameObject(parent),
	m_grid{nullptr},
	m_tileCount{0}
{

}

Grid *Tilemap::grid() const
{
	return m_grid;
}

void Tilemap::setGrid(Grid *grid)
{
	m_grid = grid;

	if (!m_grid)
		return;

	QList<Tile *> row;

	row.fill(nullptr, m_grid->columnCount());

	m_tiles.fill(row, m_grid->rowCount());
}

int Tilemap::tileCount() const
{
	return m_tileCount;
}

bool Tilemap::setTile(int row, int col, Tile *tile)
{
	if (!m_grid || row < 0 || row >= m_grid->rowCount()
		|| col < 0 || col >= m_grid->columnCount())
		return false;

	auto *oldTile = m_tiles.at(row).at(col);

	if (oldTile) {
		deleteTile(oldTile);
		addTile(row, col, tile);
	} else {
		addTile(row, col, tile);
	}

	m_tiles[row][col] = tile;

	return true;
}

bool Tilemap::resetTile(int row, int col)
{
	return setTile(row, col, nullptr);
}

bool Tilemap::hasTile(int row, int col) const
{
	return m_tiles.at(row).at(col);
}

void Tilemap::deleteTile(Tile *tile)
{
	delete tile;

	m_tileCount--;
}

void Tilemap::addTile(int row, int col, Tile *tile)
{
	if (!m_grid || !tile)
		return;

	const QSizeF &cellSize{m_grid->cellSize()};

	tile->setParentItem(this);
	tile->setPos(col*cellSize.width(), row*cellSize.height());

	m_tileCount++;
}
