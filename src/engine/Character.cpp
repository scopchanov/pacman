#include "Character.h"

Character::Character(GameObject *parent) :
	GameObject(parent)
{

}

QPointF Character::spawnPosition() const
{
	return _spawnPosition;
}

void Character::setSpawnPosition(const QPointF &point)
{
	_spawnPosition = point;

	respawn();
}

void Character::reset()
{
	respawn();

	GameObject::reset();
}

void Character::respawn()
{
	setPos(_spawnPosition);
}
