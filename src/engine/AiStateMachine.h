#ifndef AISTATEMACHINE_H
#define AISTATEMACHINE_H

#include <QObject>

class GameTimer;
class EnemyController;

class AiStateMachine : public QObject
{
	Q_OBJECT
public:
	explicit AiStateMachine(QObject *parent = nullptr);

	GameTimer *gameTimer() const;
	void setGameTimer(GameTimer *gameTimer);
	void addEnemyController(EnemyController *controller);

private:
	void changeEnemyState();
	qreal maxTime() const;
	int enemyState() const;

	GameTimer *_gameTimer;
	QList<EnemyController *> _enemyControllers;
	int _state;
	qreal _time;

private slots:
	void onGameAdvanced();
};

#endif // AISTATEMACHINE_H
