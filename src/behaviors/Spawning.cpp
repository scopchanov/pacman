#include "Spawning.h"
#include "GameObject.h"
#include "GameGlobals.h"

Spawning::Spawning(GameObject *parent) :
	AbstractBehavior(parent)
{

}

QPointF Spawning::position() const
{
	return _position;
}

void Spawning::setPosition(const QPointF &point)
{
	_position = point;

	respawn();
}

int Spawning::type() const
{
	return BT_Spawning;
}

void Spawning::reset()
{
	respawn();
}

void Spawning::respawn()
{
	if (!parent())
		return;

	parent()->setPos(_position);
}
