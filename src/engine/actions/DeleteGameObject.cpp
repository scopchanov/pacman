#include "DeleteGameObject.h"
#include "engine/objects/GameObject.h"

DeleteGameObject::DeleteGameObject(AbstractBehavior *parent) :
	AbstractAction{parent},
	_gameObject{nullptr}
{

}

GameObject *DeleteGameObject::gameObject() const
{
	return _gameObject;
}

void DeleteGameObject::setGameObject(GameObject *gameObject)
{
	_gameObject = gameObject;
}

int DeleteGameObject::type() const
{
	return ACT_DeleteGameObject;
}

void DeleteGameObject::performTask()
{
	if (!_gameObject)
		return;

	_gameObject->deleteLater();
}
