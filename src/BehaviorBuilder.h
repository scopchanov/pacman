#ifndef BEHAVIORBUILDER_H
#define BEHAVIORBUILDER_H

#include <QObject>

class Game;
class Moving;
class AbstractGameObject;
class Vector2;

class BehaviorBuilder : public QObject
{
	Q_OBJECT
public:
	explicit BehaviorBuilder(QObject *parent = nullptr);
	
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
	void addTeleporting(const QPointF &destination);

private:
	Game *game()const;
	Moving *moving() const;
	Vector2 dir2vec(int direction) const;

	AbstractGameObject *_gameObject;
};

#endif // BEHAVIORBUILDER_H
