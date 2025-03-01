#ifndef AISTATEMACHINE_H
#define AISTATEMACHINE_H

#include <QObject>

class Clock;
class ControlEnemy;

class AiStateMachine : public QObject
{
	Q_OBJECT
public:
	explicit AiStateMachine(QObject *parent = nullptr);

	void setClock(Clock *clock);
	void addEnemyController(ControlEnemy *controller);

	void advance();
	void reset();

private:
	void changeEnemyState();
	qreal maxTime() const;
	int enemyState() const;

	Clock *_clock;
	QList<ControlEnemy *> _enemyControllers;
	int _step;
	qreal _time;
};

#endif // AISTATEMACHINE_H
