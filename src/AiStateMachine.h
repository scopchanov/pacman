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

	Clock *gameClock() const;
	void setGameClock(Clock *clock);
	void addEnemyController(EnemyControlling *controller);

	void reset();

private:
	void changeEnemyState();
	qreal maxTime() const;
	int enemyState() const;

	Clock *_gameClock;
	QList<EnemyControlling *> _enemyControllers;
	int _step;
	qreal _time;

private slots:
	void onGameAdvanced();
};

#endif // AISTATEMACHINE_H
