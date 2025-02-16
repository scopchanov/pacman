#include "GameScene.h"
#include "InputSystem.h"
#include "GameObject.h"
#include <QGraphicsItem>
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

void GameScene::scheduleDelete(QGraphicsItem *item)
{
	if (_scheduledItems.contains(item))
		return;

	_scheduledItems.append(item);
}

void GameScene::makeTurn()
{
	advance();
	deleteScheduledItems();
}

void GameScene::reset()
{
	const QList<QGraphicsItem *> &childItems{items()};

	for (auto *item : childItems)
		if (item->type() == GameObject::IT_GameObject)
			static_cast<GameObject *>(item)->reset();
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Left:
		_inputSystem->setUserInput(V2_LEFT);
		break;
	case Qt::Key_Right:
		_inputSystem->setUserInput(V2_RIGHT);
		break;
	case Qt::Key_Up:
		_inputSystem->setUserInput(V2_UP);
		break;
	case Qt::Key_Down:
		_inputSystem->setUserInput(V2_DOWN);
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

void GameScene::deleteScheduledItems()
{
	while (!_scheduledItems.isEmpty()) {
		auto *item{_scheduledItems.takeFirst()};

		removeItem(item);
		delete item;
	}
}
