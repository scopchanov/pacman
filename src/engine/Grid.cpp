#include "Grid.h"
#include "Vector2.h"
#include <QPointF>

Grid::Grid(QObject *parent) :
	QObject(parent),
	_rowCount{0},
	_columnCount{0}
{

}

int Grid::rowCount() const
{
	return _rowCount;
}

int Grid::columnCount() const
{
	return _columnCount;
}

void Grid::setGridSize(int rows, int columns)
{
	_rowCount = rows;
	_columnCount = columns;
}

QSizeF Grid::cellSize() const
{
	return _cellSize;
}

void Grid::setCellSize(const QSizeF &sz)
{
	_cellSize = sz;
}

QPoint Grid::mapToGrid(const QPointF &position) const
{
	qreal row{floor(position.y()/_cellSize.height())};
	qreal col{floor(position.x()/_cellSize.width())};

	return QPoint(col, row);
}

Vector2 Grid::mapFromGrid(int row, int col)
{
	qreal x{_cellSize.width()*(col + 0.5)};
	qreal y{_cellSize.height()*(row + 0.5)};

	return Vector2(x, y);
}

Vector2 Grid::mapFromGrid(const Vector2 &cell)
{
	return mapFromGrid(cell.y(), cell.x());
}
