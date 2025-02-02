#ifndef GRID_H
#define GRID_H

#include <QPointF>
#include <QSizeF>

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
	QPointF cellPosition(int row, int col);

private:
	int m_rowCount;
	int m_columnCount;
	QSizeF m_cellSize;
};

#endif // GRID_H
