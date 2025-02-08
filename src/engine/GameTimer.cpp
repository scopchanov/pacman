#include "GameTimer.h"
#include "GameScene.h"
#include <QElapsedTimer>
#include <QTimer>

GameTimer::GameTimer(QObject *parent) :
	QObject{parent},
	_scene{nullptr},
	_time{new QElapsedTimer()},
	_timer{new QTimer(this)}
{
	connect(_timer, &QTimer::timeout, this, &GameTimer::onTimeout);
}

GameTimer::~GameTimer()
{
	delete _time;
}

qreal GameTimer::deltaTime() const
{
	return _time->elapsed()/1000.0;
}

void GameTimer::setScene(GameScene *scene)
{
	_scene = scene;

	connect(_scene, &GameScene::pauseGame, this, &GameTimer::stop);
	connect(_scene, &GameScene::resumeGame, this, &GameTimer::start);
}

void GameTimer::start()
{
	if (_timer->isActive())
		return;

	_timer->start(30);
	_time->start();
}

void GameTimer::pause()
{
	_timer->stop();
}

void GameTimer::stop()
{
	_timer->stop();
}

void GameTimer::onTimeout()
{
	if (!_scene || !_timer->isActive())
		return;

	_scene->advance();

	emit gameAdvanced();

	_time->restart();
}
