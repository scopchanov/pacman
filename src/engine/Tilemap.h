#ifndef TILEMAP_H
#define TILEMAP_H

#include <QGraphicsPathItem>

class Grid;
class Vector2;

class Tilemap : public QGraphicsPathItem
{
public:
	explicit Tilemap(QGraphicsItem *parent = nullptr);

	Grid *grid() const;
	void setGrid(Grid *grid);
	int tileCount() const;
	bool setTile(int row, int col, QGraphicsPathItem *tile);
	bool resetTile(int row, int col);
    bool hasTile(int row, int col) const;
	bool hasTile(const Vector2 &cell) const;

	void clear();

private:
	void deleteTile(QGraphicsPathItem *tile);
	void addTile(int row, int col, QGraphicsPathItem *tile);

	Grid *_grid;
	QList<QList<QGraphicsPathItem *>> _tiles;
	int _tileCount;
};

#endif // TILEMAP_H
