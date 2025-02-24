#ifndef AISTATEMACHINE_H
#define AISTATEMACHINE_H

#include <QObject>

class Clock;
class EnemyControlling;

class AiStateMachine : public QObject
{
	Q_OBJECT
public:
	explicit AiStateMachine(QObject *parent = nullptr);

	void setClock(Clock *clock);
	void addEnemyController(EnemyControlling *controller);

	void advance();
	void reset();

private:
	void changeEnemyState();
	qreal maxTime() const;
	int enemyState() const;

	Clock *_clock;
	QList<EnemyControlling *> _enemyControllers;
	int _step;
	qreal _time;
};

#endif // AISTATEMACHINE_H
