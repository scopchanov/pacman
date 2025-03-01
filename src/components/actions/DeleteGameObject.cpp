#include "DeleteGameObject.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"

DeleteGameObject::DeleteGameObject(AbstractComponent *parent) :
	AbstractAction{parent},
	_gameObject{nullptr}
{

}

AbstractGameObject *DeleteGameObject::gameObject() const
{
	return _gameObject;
}

void DeleteGameObject::setGameObject(AbstractGameObject *gameObject)
{
	_gameObject = gameObject;
}

int DeleteGameObject::type() const
{
	return ACT_DeleteGameObject;
}

void DeleteGameObject::performTasks()
{
	if (!_gameObject)
		return;

	_gameObject->deleteLater();
}
