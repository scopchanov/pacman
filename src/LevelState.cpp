#include "LevelState.h"
#include "Clock.h"
#include "Game.h"
#include "GameLevel.h"
#include "GameGlobals.h"

LevelState::LevelState(QObject *parent) :
	QObject{parent},
	_step{0},
	_time{0.0}
{

}

void LevelState::setStepDuration(int step, qreal duration)
{
	_stepDurations.insert(step, duration);
}

int LevelState::step() const
{
	return _step;
}

void LevelState::setStep(int step)
{
	_step = step;

	emit modeChanged(mode());
}

void LevelState::incrementStep()
{
	setStep(step() + 1);
}

void LevelState::advance()
{
	if (_step > _stepDurations.count() - 2)
		return;

	_time += Game::ref().level()->clock()->deltaTime();

	if (_time < _stepDurations.value(_step))
		return;

	_time = 0.0;
	incrementStep();
}

void LevelState::reset()
{
	_time = 0.0;
	setStep(0);
}

int LevelState::mode() const
{
	return _step % 2 ? WM_Chase : WM_Scatter;
}
