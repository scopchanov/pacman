#include "GameController.h"
#include "engine/GameTimer.h"

GameController::GameController(QObject *parent) :
	QObject{parent},
	m_gameTimer{new GameTimer(this)},
	m_lifeCount{3},
	m_score{0}
{

}

GameTimer *GameController::gameTimer() const
{
	return m_gameTimer;
}

int GameController::lifeCount() const
{
	return m_lifeCount;
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
	m_lifeCount++;

	emit lifeCountChanged(m_lifeCount);
}

void GameController::removeLife()
{
	m_lifeCount--;

	emit lifeCountChanged(m_lifeCount);
}

void GameController::start()
{
	m_gameTimer->start();
}
