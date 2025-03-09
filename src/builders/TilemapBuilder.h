#ifndef TILEMAPBUILDER_H
#define TILEMAPBUILDER_H

#include <QObject>
#include <QPen>

class QGraphicsItem;
class Tilemap;
class Grid;

class TilemapBuilder : public QObject
{
	Q_OBJECT
public:
	explicit TilemapBuilder(QObject *parent = nullptr);

	Tilemap *tilemap() const;
	void setTilemap(Tilemap *tilemap);
	Grid *grid() const;
	void setGrid(Grid *grid);
	QPen pen() const;
	void setPen(const QPen &pen);
	QBrush brush() const;
	void setBrush(const QBrush &brush);

	void build(const QJsonArray &matrix);
	void setTile(int row, int col, int pathIndex);

private:
	QGraphicsItem *createTile(int pathIndex);

	Tilemap *_tilemap;
	Grid *_grid;
	QPen _pen;
	QBrush _brush;
};

#endif // TILEMAPBUILDER_H
