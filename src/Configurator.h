#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QObject>

class QGraphicsItem;
class AbstractPersonality;
class GameLevel;
class Palette;
class Grid;
class Tilemap;

class Configurator : public QObject
{
	Q_OBJECT
public:
	explicit Configurator(QObject *parent = nullptr);
	
	void configure(const QJsonObject &json);

private:
	void configurePalette(const QJsonObject &json);
	void configureGrid(const QJsonObject &json);
	void configureWalls(const QJsonArray &jsonWalls);
	void configureDots(const QJsonArray &jsonDots);
	void configurePlayer(const QJsonObject &json);
	void createEnemies(const QJsonArray &enemies);
	void createEnemy(const QJsonObject &json);
	AbstractPersonality *createPersonality(const QJsonObject &json);
	void createDoors(const QJsonArray &doors);
	void createDoor(const QJsonObject &json);
	void createEnergizers(const QJsonArray &energizers);
	void createEnergizer(const QJsonObject &json);
	void createTeleporters(const QJsonArray &teleporters);
	void createTeleporter(const QJsonObject &json);
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	QGraphicsItem *createTile(int index, const QPen &pen, const QBrush &brush);
	int key2role(const QString &key) const;
	QPointF gridPosition(int row, int column) const;
	GameLevel *level() const;
	Palette *palette() const;
	Grid *grid() const;
};

#endif // CONFIGURATOR_H
