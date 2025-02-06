#ifndef GRID_H
#define GRID_H

#include <QPointF>
#include <QSizeF>

class Vector2;

class Grid
{
public:
	explicit Grid();

	int rowCount() const;
	int columnCount() const;
	void setGridSize(int rows, int columns);
	QSizeF cellSize() const;
	void setCellSize(const QSizeF &sz);

	QPoint posToCell(QPointF position) const;
	Vector2 cellPosition(int row, int col);
	Vector2 cellPosition(const Vector2 &cell);

private:
	int m_rowCount;
	int m_columnCount;
	QSizeF m_cellSize;
};

#endif // GRID_H
