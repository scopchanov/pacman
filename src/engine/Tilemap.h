#ifndef TILEMAP_H
#define TILEMAP_H

#include "GameObject.h"
#include <QList>

class Tile;

class Tilemap : public GameObject
{
public:
    explicit Tilemap(QGraphicsItem *parent = nullptr);

	int gridRows() const;
	int gridColumns() const;
    void setGridSize(int rows, int columns);
    QSizeF cellSize() const;
    void setCellSize(const QSizeF &sz);
    void setCellSize(qreal width, qreal height);
	int tileCount() const;
    bool setTile(int row, int col, Tile *tile);
	bool resetTile(int row, int col);
    bool hasTile(int row, int col) const;
	QPointF cellPosition(int col, int row) const;
    QPoint posToCell(QPointF position) const;
    QPoint posToCell(qreal x, qreal y) const;

private:
	void deleteTile(Tile *tile);
	void foo(int row, int col, Tile *tile);

	int m_gridRows;
	int m_gridColumns;
    QSize m_gridSize;
    QSizeF m_cellSize;
    QList<QList<Tile *>> m_tiles;
	int m_tileCount;
};

#endif // TILEMAP_H
