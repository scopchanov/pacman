#ifndef AISTATEMACHINE_H
#define AISTATEMACHINE_H

#include <QObject>

class GameClock;
class EnemyControlling;

class AiStateMachine : public QObject
{
	Q_OBJECT
public:
	explicit AiStateMachine(QObject *parent = nullptr);

	GameClock *gameClock() const;
	void setGameClock(GameClock *clock);
	void addEnemyController(EnemyControlling *controller);

	void reset();

private:
	void changeEnemyState();
	qreal maxTime() const;
	int enemyState() const;

	GameClock *_gameClock;
	QList<EnemyControlling *> _enemyControllers;
	int _step;
	qreal _time;

private slots:
	void onGameAdvanced();
};

#endif // AISTATEMACHINE_H
