#include "Spawn.h"
#include "AbstractGameObject.h"
#include "GameGlobals.h"

Spawn::Spawn(AbstractComponent *parent) :
	AbstractAction(parent)
{

}

QPointF Spawn::position() const
{
	return _position;
}

void Spawn::setPosition(const QPointF &point)
{
	_position = point;

	respawn();
}

int Spawn::type() const
{
	return ACT_Spawn;
}

void Spawn::reset()
{
	respawn();
}

void Spawn::respawn()
{
	if (!gameObject())
		return;

	gameObject()->setPos(_position);
}
