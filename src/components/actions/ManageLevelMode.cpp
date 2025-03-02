#include "ManageLevelMode.h"
#include "Clock.h"
#include "Game.h"
#include "GameGlobals.h"
#include "objects/LevelMode.h"

ManageLevelMode::ManageLevelMode(AbstractComponent *parent) :
	AbstractTimedAction(parent),
	_time{0.0}
{

}

void ManageLevelMode::setStepDuration(int step, qreal duration)
{
	_stepDurations.insert(step, duration);
}

int ManageLevelMode::type() const
{
	return ACT_ManageLevelMode;
}

void ManageLevelMode::reset()
{
	auto *mode{levelMode()};

	_time = 0.0;

	if (mode)
		mode->setStep(0);
}

void ManageLevelMode::performTasks()
{
	auto *mode{levelMode()};

	if (!mode || mode->step() > _stepDurations.count() - 2)
		return;

	_time += Game::ref().clock()->deltaTime();

	if (_time < _stepDurations.value(mode->step()))
		return;

	mode->incrementStep();
	_time = 0.0;
}

LevelMode *ManageLevelMode::levelMode() const
{
	return gameObject() ? static_cast<LevelMode *>(gameObject()) : nullptr;
}
