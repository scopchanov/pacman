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

void Teleporting::reset()
{

}

void Teleporting::performActions()
{
	const QList<QGraphicsItem *> &collidingItems{parent()->collidingItems()};

	for (auto *item : collidingItems) {
		if (item->type() != QGraphicsItem::UserType)
			continue;

		auto *gameObject{static_cast<GameObject *>(item)};
		auto *behavior{gameObject->findBehavior(BT_CharacterMovement)};

		if (!behavior)
			continue;

		auto *movement{static_cast<CharacterMovement *>(behavior)};

		movement->relocateCharacter(m_destination);
	}
}
