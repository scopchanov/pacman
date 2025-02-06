#include "Teleporting.h"
#include "engine/GameObject.h"
#include "engine/behaviors/CharacterMovement.h"

Teleporting::Teleporting(GameObject *parent) :
	AbstractBehavior(parent)
{

}

QPointF Teleporting::destination() const
{
	return m_destination;
}

void Teleporting::setDestination(const QPointF &destination)
{
	m_destination = destination;
}

int Teleporting::type() const
{
	return BT_Teleporting;
}

void Teleporting::performActions()
{
	const QList<QGraphicsItem *> &collidingItems{parent()->collidingItems()};

	for (auto *item : collidingItems) {
		if (item->type() != QGraphicsItem::UserType)
			continue;

		auto *movement{findMovement(static_cast<GameObject *>(item))};

		if (movement)
			movement->relocateCharacter(m_destination);
	}
}

CharacterMovement *Teleporting::findMovement(GameObject *gameObject) const
{
	for (int n{0}; n < gameObject->behaviorCount(); n++) {
		auto *behavior{gameObject->behavior(n)};

		if (behavior->type() == BT_CharacterMovement)
			return static_cast<CharacterMovement *>(behavior);
	}

	return nullptr;
}
