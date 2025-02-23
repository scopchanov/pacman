#ifndef BEHAVIORBUILDER_H
#define BEHAVIORBUILDER_H

#include <QObject>

class Moving;
class GameObject;
class Vector2;

class BehaviorBuilder : public QObject
{
	Q_OBJECT
public:
	explicit BehaviorBuilder(QObject *parent = nullptr);
	
	void setGameObject(GameObject *gameObject);
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
	Moving *moving() const;
	Vector2 dir2vec(int direction) const;

	GameObject *_gameObject;
};

#endif // BEHAVIORBUILDER_H
