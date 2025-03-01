#include "AiStateMachine.h"
#include "Clock.h"
#include "components/actions/control/ControlEnemy.h"
#include <QHash>

AiStateMachine::AiStateMachine(QObject *parent) :
	QObject{parent},
	_clock{nullptr},
	_step{0},
	_time{0.0}
{

}

void AiStateMachine::setClock(Clock *clock)
{
	_clock = clock;
}

void AiStateMachine::addEnemyController(ControlEnemy *controller)
{
	_enemyControllers.append(controller);
}

void AiStateMachine::advance()
{
	if (_step > 6)
		return;

	_time += _clock->deltaTime();

	if (_time < maxTime())
		return;

	_step++;
	_time = 0.0;

	changeEnemyState();
}

void AiStateMachine::reset()
{
	_step = 0;
	_time = 0.0;
}

void AiStateMachine::changeEnemyState()
{
	ControlEnemy::GlobalState state{_step % 2 ? ControlEnemy::GS_Chase
												 : ControlEnemy::GS_Scatter};

	for (auto *enemyController : std::as_const(_enemyControllers))
		if (enemyController)
			enemyController->setGlobalState(state);
}

qreal AiStateMachine::maxTime() const
{
	return QHash<int, qreal>{{0, 7.0}, {1, 20.0}, {2, 7.0}, {3, 20.0}, {4, 5.0},
							 {5, 20.0}, {6, 5.0}, {7, 0.0}}.value(_step);
}
