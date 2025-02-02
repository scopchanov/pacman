#include "GameTimer.h"
#include "Scene.h"
#include <QElapsedTimer>
#include <QTimer>

GameTimer::GameTimer(QObject *parent) :
	QObject{parent},
	m_scene{nullptr},
	m_time{new QElapsedTimer()},
	m_timer{new QTimer(this)}
{
	connect(m_timer, &QTimer::timeout, this, &GameTimer::onTimeout);
}

GameTimer::~GameTimer()
{
	delete m_time;
}

qreal GameTimer::deltaTime() const
{
	return m_time->elapsed()/1000.0;
}

void GameTimer::setScene(Scene *scene)
{
	m_scene = scene;

	connect(m_scene, &Scene::pauseGame, this, &GameTimer::stop);
	connect(m_scene, &Scene::resumeGame, this, &GameTimer::start);
}

void GameTimer::start()
{
	if (m_timer->isActive())
		return;

	m_timer->start(30);
	m_time->start();
}

void GameTimer::pause()
{
	m_timer->stop();
}

void GameTimer::stop()
{
	m_timer->stop();
}

void GameTimer::onTimeout()
{
	if (!m_scene || !m_timer->isActive())
		return;

	m_scene->advance();
	m_time->restart();
}
