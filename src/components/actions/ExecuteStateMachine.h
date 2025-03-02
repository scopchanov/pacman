#ifndef EXECUTESTATEMACHINE_H
#define EXECUTESTATEMACHINE_H

#include "AbstractTimedAction.h"

class ControlEnemy;

class ExecuteStateMachine : public AbstractTimedAction
{
	Q_OBJECT
public:
	explicit ExecuteStateMachine(AbstractComponent *parent = nullptr);

	int step() const;
	int type() const override;
	void reset() override;

protected:
	void performTasks() override;

private:
	qreal maxTime() const;

	int _step;
	qreal _time;
};

#endif // EXECUTESTATEMACHINE_H
