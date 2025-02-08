#include "GameScene.h"
#include "InputSystem.h"
#include <QKeyEvent>

GameScene::GameScene(QObject *parent) :
	QGraphicsScene{parent},
	_inputSystem{new InputSystem(this)}
{

}

InputSystem *GameScene::inputSystem() const
{
	return _inputSystem;
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Left:
		_inputSystem->setUserInput(Vector2(-1, 0));
		break;
	case Qt::Key_Right:
		_inputSystem->setUserInput(Vector2(1, 0));
		break;
	case Qt::Key_Up:
		_inputSystem->setUserInput(Vector2(0, -1));
		break;
	case Qt::Key_Down:
		_inputSystem->setUserInput(Vector2(0, 1));
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
