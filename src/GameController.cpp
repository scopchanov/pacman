#include "GameController.h"
#include "engine/GameTimer.h"

GameController::GameController(QObject *parent) :
	QObject{parent},
	m_gameTimer{new GameTimer(this)},
	m_lifesLeft{2},
	m_score{0}
{

}

GameTimer *GameController::gameTimer() const
{
	return m_gameTimer;
}

int GameController::lifesLeft() const
{
	return m_lifesLeft;
}

int GameController::score() const
{
	return m_score;
}

void GameController::increaseScore(int amount)
{
	m_score += amount;

	emit scoreChanged(m_score);
}

void GameController::addLife()
{
	m_lifesLeft++;

	emit lifesLeftChanged(m_lifesLeft);
}

void GameController::removeLife()
{
	m_lifesLeft--;

	emit lifesLeftChanged(m_lifesLeft);
}

void GameController::start()
{
	m_gameTimer->start();
}
