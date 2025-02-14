#include "GameClock.h"
#include <QElapsedTimer>
#include <QTimer>

GameClock::GameClock(QObject *parent) :
	QObject{parent},
	_time{new QElapsedTimer()},
	_timer{new QTimer(this)}
{
	connect(_timer, &QTimer::timeout, this, &GameClock::onTimeout);
}

GameClock::~GameClock()
{
	delete _time;
}

qreal GameClock::deltaTime() const
{
	return _time->elapsed()/1000.0;
}

void GameClock::start()
{
	if (_timer->isActive())
		return;

	_timer->start(16); // 30
	_time->start();
}

void GameClock::stop()
{
	_timer->stop();
}

void GameClock::onTimeout()
{
	if (!_timer->isActive())
		return;

	emit tick();

	_time->restart();
}
