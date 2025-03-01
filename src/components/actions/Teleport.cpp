#include "Teleport.h"
#include "AbstractGameObject.h"
#include "GameGlobals.h"
#include "components/actions/tilemap/Move.h"

Teleport::Teleport(AbstractComponent *parent) :
	AbstractAction(parent)
{

}

QPointF Teleport::destination() const
{
	return _destination;
}

void Teleport::setDestination(const QPointF &destination)
{
	_destination = destination;
}

int Teleport::type() const
{
	return ACT_Teleport;
}

void Teleport::performTasks()
{
	const auto &collidingObjects{gameObject()->collidingObjects()};

	for (auto *object : collidingObjects)
		teleport(object);
}

void Teleport::teleport(AbstractGameObject *gameObject)
{
	auto *move{gameObject->findComponent(ACT_Move)};

	if (move)
		static_cast<Move *>(move)->relocateCharacter(_destination);
}
