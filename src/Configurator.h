#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QObject>

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
	void createEnemies(const QJsonArray &enemies);
	Enemy *createEnemy(const QPointF &position, const QColor &color, int direction);
	GameObject *createEnergizer(const QPoint &cell);
	GameObject *createTeleporter(const QPointF &src, const QPointF &dst);
	AbstractPersonality *createPersonality(int type);
	Vector2 dir2vec(int direction);
};

#endif // CONFIGURATOR_H
