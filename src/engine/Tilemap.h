#ifndef TILEMAP_H
#define TILEMAP_H

#include "GameObject.h"

class Grid;
class Tile;

class Tilemap : public GameObject
{
public:
    explicit Tilemap(QGraphicsItem *parent = nullptr);

	Grid *grid() const;
	void setGrid(Grid *grid);
	int tileCount() const;
    bool setTile(int row, int col, Tile *tile);
	bool resetTile(int row, int col);
    bool hasTile(int row, int col) const;

private:
	void deleteTile(Tile *tile);
	void addTile(int row, int col, Tile *tile);

	Grid *m_grid;
    QList<QList<Tile *>> m_tiles;
	int m_tileCount;
};

#endif // TILEMAP_H
