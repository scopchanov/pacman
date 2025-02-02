#include "Grid.h"

Grid::Grid() :
	m_rowCount{0},
	m_columnCount{0}
{

}

int Grid::rowCount() const
{
	return m_rowCount;
}

int Grid::columnCount() const
{
	return m_columnCount;
}

void Grid::setGridSize(int rows, int columns)
{
	m_rowCount = rows;
	m_columnCount = columns;
}

QSizeF Grid::cellSize() const
{
	return m_cellSize;
}

void Grid::setCellSize(const QSizeF &sz)
{
	m_cellSize = sz;
}

QPoint Grid::posToCell(QPointF position) const
{
	qreal row{floor(position.y()/m_cellSize.height())};
	qreal col{floor(position.x()/m_cellSize.width())};

	return QPoint(col, row);
}

QPointF Grid::cellPosition(int row, int col)
{
	qreal x{m_cellSize.width()*(col + 0.5)};
	qreal y{m_cellSize.height()*(row + 0.5)};

	return QPointF(x, y);
}
