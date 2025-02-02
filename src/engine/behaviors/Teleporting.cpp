#include "Teleporting.h"
#include "engine/GameObject.h"
#include <QDebug>

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

void Teleporting::performActions()
{
	for (auto *item : parent()->collidingItems())
		item->setPos(m_destination);
}
