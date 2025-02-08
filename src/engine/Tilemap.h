#ifndef TILEMAP_H
#define TILEMAP_H

#include "GameObject.h"

class Grid;
class Tile;
class Vector2;

class Tilemap : public GameObject
{
public:
	explicit Tilemap(GameObject *parent = nullptr);

	Grid *grid() const;
	void setGrid(Grid *grid);
	int tileCount() const;
    bool setTile(int row, int col, Tile *tile);
	bool resetTile(int row, int col);
    bool hasTile(int row, int col) const;
	bool hasTile(const Vector2 &cell) const;

private:
	void deleteTile(Tile *tile);
	void addTile(int row, int col, Tile *tile);

	Grid *_grid;
	QList<QList<Tile *>> _tiles;
	int _tileCount;
};

#endif // TILEMAP_H
