#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QObject>

class AbstractPersonality;
class Game;
class GameObject;
class Ghost;
class Tile;
class Tilemap;
class Vector2;

class Configurator : public QObject
{
	Q_OBJECT
public:
	explicit Configurator(QObject *parent = nullptr);

	void configure(const QJsonObject &json);

	Game *game() const;
	void setGame(Game *game);

private:
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	Tile *createTile(int index, const QPen &pen, const QBrush &brush);
	void createEnemies(const QJsonArray &enemies);
	Ghost *createEnemy(const QPointF &position, const QColor &color, int direction);
	GameObject *createPowerUp(const QPoint &cell);
	GameObject *createTeleporter(const QPointF &src, const QPointF &dst);
	AbstractPersonality *createPersonality(int type);
	Vector2 dir2vec(int direction);

	Game *_game;
};

#endif // CONFIGURATOR_H
