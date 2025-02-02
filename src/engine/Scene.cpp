#include "Scene.h"
#include "InputSystem.h"
#include <QKeyEvent>

Scene::Scene(QObject *parent) :
	QGraphicsScene{parent},
	m_inputSystem{new InputSystem(this)}
{

}

InputSystem *Scene::inputSystem() const
{
	return m_inputSystem;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Left:
		m_inputSystem->setUserInput(Vector2(-1, 0));
		break;
	case Qt::Key_Right:
		m_inputSystem->setUserInput(Vector2(1, 0));
		break;
	case Qt::Key_Up:
		m_inputSystem->setUserInput(Vector2(0, -1));
		break;
	case Qt::Key_Down:
		m_inputSystem->setUserInput(Vector2(0, 1));
		break;
	case Qt::Key_Escape:
		emit pauseGame();
		break;
	case Qt::Key_Space:
		emit resumeGame();
		break;
	default:
		break;
	}

}
