#include "AiStateMachine.h"
#include "GameClock.h"
#include "engine/behaviors/EnemyController.h"
#include <QHash>

AiStateMachine::AiStateMachine(QObject *parent) :
	QObject{parent},
	_gameClock{nullptr},
	_step{0},
	_time{0.0}
{

}

GameClock *AiStateMachine::gameClock() const
{
	return _gameClock;
}

void AiStateMachine::setGameClock(GameClock *clock)
{
	_gameClock = clock;

	connect(clock, &GameClock::tick, this, &AiStateMachine::onGameAdvanced);
}

void AiStateMachine::addEnemyController(EnemyController *controller)
{
	_enemyControllers.append(controller);
}

void AiStateMachine::reset()
{
	_step = 0;
	_time = 0.0;
}

void AiStateMachine::changeEnemyState()
{
	EnemyController::GlobalState state{_step % 2 ? EnemyController::GS_Chase
												 : EnemyController::GS_Scatter};

	for (auto *enemyController : std::as_const(_enemyControllers))
		enemyController->setGlobalState(state);
}

qreal AiStateMachine::maxTime() const
{
	return QHash<int, qreal>{{0, 7.0}, {1, 20.0}, {2, 7.0}, {3, 20.0}, {4, 5.0},
							 {5, 20.0}, {6, 5.0}, {7, 0.0}}.value(_step);
}

void AiStateMachine::onGameAdvanced()
{
	if (_step > 6)
		return;

	_time += _gameClock->deltaTime();

	if (_time < maxTime())
		return;

	_step++;
	_time = 0.0;

	changeEnemyState();
}
