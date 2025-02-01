#include "Tilemap.h"
#include "Tile.h"

Tilemap::Tilemap(QGraphicsItem *parent) :
	GameObject(parent),
	m_gridRows{0},
	m_gridColumns{0},
	m_cellSize{QSizeF(64, 64)},
	m_tileCount{0}
{

}

int Tilemap::gridRows() const
{
	return m_gridRows;
}

int Tilemap::gridColumns() const
{
	return m_gridColumns;
}

void Tilemap::setGridSize(int rows, int columns)
{
	m_gridRows = rows;
	m_gridColumns = columns;

	QList<Tile *> row;

	row.fill(nullptr, m_gridColumns);

	m_tiles.fill(row, m_gridRows);
}

QSizeF Tilemap::cellSize() const
{
	return m_cellSize;
}

void Tilemap::setCellSize(const QSizeF &sz)
{
	m_cellSize = sz;
}

void Tilemap::setCellSize(qreal width, qreal height)
{
	setCellSize(QSizeF(width, height));
}

int Tilemap::tileCount() const
{
	return m_tileCount;
}

bool Tilemap::setTile(int row, int col, Tile *tile)
{
	if (row < 0 || row >= m_gridRows || col < 0 || col >= m_gridColumns)
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

QPointF Tilemap::cellPosition(int col, int row) const
{
	return QPointF(col*m_cellSize.width(), row*m_cellSize.height());
}

QPoint Tilemap::posToCell(QPointF position) const
{
	return posToCell(position.x(), position.y());
}

QPoint Tilemap::posToCell(qreal x, qreal y) const
{
	return QPoint(floor(x/m_cellSize.width()), floor(y/m_cellSize.height()));
}

void Tilemap::deleteTile(Tile *tile)
{
	delete tile;

	m_tileCount--;
}

void Tilemap::addTile(int row, int col, Tile *tile)
{
	if (!tile)
		return;

	tile->setParentItem(this);
	tile->setPos(col*m_cellSize.width(), row*m_cellSize.height());

	m_tileCount++;
}
