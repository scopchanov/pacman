#ifndef COMPONENTBUILDER_H
#define COMPONENTBUILDER_H

#include <QObject>

using StepDurations = QList<QPair<int, qreal>>;

class Game;
class Move;
class AbstractGameObject;
class Vector2;

class ComponentBuilder : public QObject
{
	Q_OBJECT
public:
	explicit ComponentBuilder(QObject *parent = nullptr);
	
	void setGameObject(AbstractGameObject *gameObject);
	void addManageLevelMode(const StepDurations &stepDurations);
	void addSpawn(const QPointF &position);
	void addMove(int direction);
	void addControl(int type);
	void addOrientate(int type, Move *move);
	void addAnimate(int type);
	void addEatDot();
	void addEatEnemy();
	void addKillPlayer();
	void addEnergizePlayer();
	void addUpdateDeenergizer();
	void addTeleport(const QPointF &destination);

private:
	Game *game()const;
	Move *move() const;
	Vector2 dir2vec(int direction) const;

	AbstractGameObject *_gameObject;
};

#endif // COMPONENTBUILDER_H
