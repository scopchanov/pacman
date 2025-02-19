#include "GameStatus.h"

GameStatus::GameStatus(QObject *parent) :
	QObject{parent},
	_lifesLeft{2},
	_score{0}
{

}

int GameStatus::lifesLeft() const
{
	return _lifesLeft;
}

int GameStatus::score() const
{
	return _score;
}

void GameStatus::increaseScore(int amount)
{
	_score += amount;

	emit scoreChanged(_score);
}

void GameStatus::reset()
{
	_score = 0;
	_lifesLeft = 2;

	emit scoreChanged(_score);
	emit lifesLeftChanged(_lifesLeft);
}

void GameStatus::addLife()
{
	_lifesLeft++;

	emit lifesLeftChanged(_lifesLeft);
}

void GameStatus::removeLife()
{
	_lifesLeft--;

	emit lifesLeftChanged(_lifesLeft);
}
