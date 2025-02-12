#include "GameController.h"
#include "engine/GameTimer.h"

GameController::GameController(QObject *parent) :
	QObject{parent},
	_gameTimer{new GameTimer(this)},
	_lifesLeft{2},
	_score{0}
{

}

GameTimer *GameController::gameTimer() const
{
	return _gameTimer;
}

int GameController::lifesLeft() const
{
	return _lifesLeft;
}

int GameController::score() const
{
	return _score;
}

void GameController::increaseScore(int amount)
{
	_score += amount;

	emit scoreChanged(_score);
}

void GameController::reset()
{
	_score = 0;
	_lifesLeft = 2;

	emit scoreChanged(_score);
	emit lifesLeftChanged(_lifesLeft);
}

void GameController::addLife()
{
	_lifesLeft++;

	emit lifesLeftChanged(_lifesLeft);
}

void GameController::removeLife()
{
	_lifesLeft--;

	emit lifesLeftChanged(_lifesLeft);
}

void GameController::start()
{
	_gameTimer->start();
}
