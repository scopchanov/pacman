#include "ManageLevelState.h"
#include "Clock.h"
#include "Game.h"
#include "GameGlobals.h"
#include "objects/LevelState.h"

ManageLevelState::ManageLevelState(AbstractComponent *parent) :
	AbstractTimedAction(parent),
	_time{0.0}
{

}

void ManageLevelState::setStepDuration(int step, qreal duration)
{
	_stepDurations.insert(step, duration);
}

int ManageLevelState::type() const
{
	return ACT_ManageLevelState;
}

void ManageLevelState::reset()
{
	auto *state{levelState()};

	_time = 0.0;

	if (state)
		state->setStep(0);
}

void ManageLevelState::performTasks()
{
	auto *state{levelState()};

	if (!state || state->step() > _stepDurations.count() - 2)
		return;

	_time += Game::ref().clock()->deltaTime();

	if (_time < _stepDurations.value(state->step()))
		return;

	state->incrementStep();
	_time = 0.0;
}

LevelState *ManageLevelState::levelState() const
{
	return gameObject() ? static_cast<LevelState *>(gameObject()) : nullptr;
}
