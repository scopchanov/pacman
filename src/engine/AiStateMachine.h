#ifndef AISTATEMACHINE_H
#define AISTATEMACHINE_H

#include <QObject>

class GameClock;
class EnemyController;

class AiStateMachine : public QObject
{
	Q_OBJECT
public:
	explicit AiStateMachine(QObject *parent = nullptr);

	GameClock *gameClock() const;
	void setGameClock(GameClock *clock);
	void addEnemyController(EnemyController *controller);

	void reset();

private:
	void changeEnemyState();
	qreal maxTime() const;
	int enemyState() const;

	GameClock *_gameClock;
	QList<EnemyController *> _enemyControllers;
	int _state;
	qreal _time;

private slots:
	void onGameAdvanced();
};

#endif // AISTATEMACHINE_H
