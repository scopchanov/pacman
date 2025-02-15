#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QSizeF>

class Vector2;

class Grid : public QObject
{
	Q_OBJECT
public:
	explicit Grid(QObject *parent = nullptr);

	int rowCount() const;
	int columnCount() const;
	void setGridSize(int rows, int columns);
	QSizeF cellSize() const;
	void setCellSize(const QSizeF &sz);

	QPoint mapToGrid(const QPointF &position) const;
	Vector2 mapFromGrid(int row, int col);
	Vector2 mapFromGrid(const Vector2 &cell);

private:
	int _rowCount;
	int _columnCount;
	QSizeF _cellSize;
};

#endif // GRID_H
