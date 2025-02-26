#ifndef COMPONENTBUILDER_H
#define COMPONENTBUILDER_H

#include <QObject>

class Game;
class Moving;
class AbstractGameObject;
class Vector2;

class ComponentBuilder : public QObject
{
	Q_OBJECT
public:
	explicit ComponentBuilder(QObject *parent = nullptr);
	
	void setGameObject(AbstractGameObject *gameObject);
	void addColoring(const QColor &color);
	void addSpawning(const QPointF &position);
	void addMoving(int direction);
	void addControlling(int type);
	void addOrientating(int type);
	void addAnimating(int type);
	void addDotsEating();
	void addEnemyEating();
	void addKilling();
	void addEnergizing();
	void addTeleport(const QPointF &destination);

private:
	Game *game()const;
	Moving *moving() const;
	Vector2 dir2vec(int direction) const;

	AbstractGameObject *_gameObject;
};

#endif // COMPONENTBUILDER_H
