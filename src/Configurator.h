#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QObject>

class QGraphicsItem;
class GameLevel;
class GamePalette;
class Grid;
class Tilemap;

class Configurator : public QObject
{
	Q_OBJECT
public:
	explicit Configurator(QObject *parent = nullptr);
	
	void configure(const QJsonObject &json);

private:
	GameLevel *level() const;
	GamePalette *palette() const;
	Grid *grid() const;
	void configurePalette(const QJsonObject &json);
	void configureGrid(const QJsonObject &json);
	void configurePlayer(const QJsonObject &json);
	void createEnemies(const QJsonArray &enemies);
	void createEnemy(const QJsonObject &json);
	void createEnergizers(const QJsonArray &energizers);
	void createEnergizer(const QJsonObject &json);
	void createTeleporters(const QJsonArray &teleporters);
	void createTeleporter(const QJsonObject &json);
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	QGraphicsItem *createTile(int index, const QPen &pen, const QBrush &brush);
	int key2role(const QString &key) const;
};

#endif // CONFIGURATOR_H
