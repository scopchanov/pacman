#include "ExecuteStateMachine.h"
#include "Clock.h"
#include "Game.h"
#include "GameGlobals.h"
#include <QHash>

ExecuteStateMachine::ExecuteStateMachine(AbstractComponent *parent) :
	AbstractTimedAction(parent),
	_step{0},
	_time{0.0}
{

}

int ExecuteStateMachine::step() const
{
	return _step;
}

int ExecuteStateMachine::type() const
{
	return ACT_ExecuteStateMachine;
}

void ExecuteStateMachine::reset()
{
	_step = 0;
	_time = 0.0;
}

void ExecuteStateMachine::performTasks()
{
	if (_step > 6)
		return;

	_time += Game::ref().clock()->deltaTime();

	if (_time < maxTime())
		return;

	_step++;
	_time = 0.0;
}

qreal ExecuteStateMachine::maxTime() const
{
	return QHash<int, qreal>{{0, 7.0}, {1, 20.0}, {2, 7.0}, {3, 20.0}, {4, 5.0},
							 {5, 20.0}, {6, 5.0}, {7, 0.0}}.value(_step);
}
