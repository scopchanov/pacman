#include "GameController.h"
#include <QGraphicsScene>
#include <QElapsedTimer>
#include <QTimer>
#include <QDebug>

GameController::GameController(QObject *parent) :
    QObject{parent},
    m_scene{nullptr},
    m_time{new QElapsedTimer()},
    m_timer{new QTimer(this)}
{
    m_timer->setTimerType(Qt::PreciseTimer);
    m_timer->setSingleShot(false);
	m_timer->setInterval(16);

    connect(m_timer, &QTimer::timeout, this, &GameController::onTimeout);
}

GameController::~GameController()
{
    delete m_time;
}

qreal GameController::deltaTime() const
{
	return m_time->elapsed()/1000.0;
}

void GameController::setScene(QGraphicsScene *scene)
{
    m_scene = scene;
}

void GameController::start()
{
    if (m_timer->isActive())
        return;

    m_timer->start();
    m_time->start();
}

void GameController::stop()
{
	m_timer->stop();
}

void GameController::onTimeout()
{
	if (!m_scene || !m_timer->isActive())
        return;

    m_scene->advance();
    m_time->restart();
}
