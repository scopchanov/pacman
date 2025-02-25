#include "Teleporting.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "behaviors/Moving.h"

Teleporting::Teleporting(AbstractGameObject *parent) :
	AbstractBehavior(parent)
{

}

QPointF Teleporting::destination() const
{
	return _destination;
}

void Teleporting::setDestination(const QPointF &destination)
{
	_destination = destination;
}

int Teleporting::type() const
{
	return BT_Teleporting;
}

void Teleporting::performActions()
{
	const auto &collidingObjects{parent()->collidingObjects()};

	for (auto *gameObject : collidingObjects)
		teleport(gameObject);
}

void Teleporting::teleport(AbstractGameObject *gameObject)
{
	auto *moving{gameObject->findBehavior(BT_Moving)};

	if (moving)
		static_cast<Moving *>(moving)->relocateCharacter(_destination);
}
