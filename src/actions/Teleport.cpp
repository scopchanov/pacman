#include "Teleport.h"
#include "AbstractGameObject.h"
#include "GameGlobals.h"
#include "behaviors/Moving.h"

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
	auto *moving{gameObject->findComponent(BT_Moving)};

	if (moving)
		static_cast<Moving *>(moving)->relocateCharacter(_destination);
}
