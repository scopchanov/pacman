#include "Teleporting.h"
#include "GameGlobals.h"
#include "GameObject.h"
#include "behaviors/CharacterMovement.h"

Teleporting::Teleporting(GameObject *parent) :
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

void Teleporting::teleport(GameObject *gameObject)
{
	auto *behavior{gameObject->findBehavior(BT_CharacterMovement)};

	if (!behavior)
		return;

	auto *movement{static_cast<CharacterMovement *>(behavior)};

	movement->relocateCharacter(_destination);
}
