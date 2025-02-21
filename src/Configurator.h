#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QObject>

class QGraphicsItem;
class AbstractPersonality;
class Game;
class GameObject;
class Enemy;
class Tilemap;
class Vector2;

class Configurator : public QObject
{
	Q_OBJECT
public:
	explicit Configurator(QObject *parent = nullptr);

	void configure(const QJsonObject &json);

private:
	void configurePalette(const QJsonObject &jsonPalette);
	void setupPlayer(const QJsonObject &jsonPlayer);
	void createEnemies(const QJsonObject &json);
	Enemy *createEnemy(const QPointF &position, const QColor &color, int direction);
	GameObject *createEnergizer(const QPoint &cell);
	GameObject *createTeleporter(const QPointF &src, const QPointF &dst);
	AbstractPersonality *createPersonality(int type);
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	QGraphicsItem *createTile(int index, const QPen &pen, const QBrush &brush);
	Vector2 dir2vec(int direction) const;
	int key2role(const QString &key) const;
};

#endif // CONFIGURATOR_H
