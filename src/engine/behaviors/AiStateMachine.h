#ifndef AISTATEMACHINE_H
#define AISTATEMACHINE_H

#include <QObject>

class EnemyController;

class AiStateMachine : public QObject
{
	Q_OBJECT
public:
	explicit AiStateMachine(QObject *parent = nullptr);

	void setFoo(EnemyController *ctrl);

	void dodd();

	void switchStates();

private:
	EnemyController *m_c;

	int _state;
	QTimer *m_timer;
};

#endif // AISTATEMACHINE_H
