#include "GameObject.h"
#include "behaviors/AbstractBehavior.h"
#include "Vector2.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>

// #define DEBUG

GameObject::GameObject(GameObject *parent) :
	QGraphicsPathItem(parent)
{

}

GameObject::~GameObject()
{
	while (!m_behaviors.isEmpty())
		delete m_behaviors.takeFirst();
}

void GameObject::addBehavior(AbstractBehavior *behavior)
{
	m_behaviors.append(behavior);
}

int GameObject::behaviorCount() const
{
	return m_behaviors.count();
}

AbstractBehavior *GameObject::behavior(int n) const
{
	return m_behaviors.at(n);
}

AbstractBehavior *GameObject::findBehavior(int type) const
{
	for (auto *behavior : std::as_const(m_behaviors))
		if (behavior->type() == type)
			return behavior;

	return nullptr;
}

int GameObject::type() const
{
	return QGraphicsItem::UserType;
}

void GameObject::advance(int phase)
{
	if (!phase)
		return;

	for (auto *behavior : std::as_const(m_behaviors))
		behavior->execute();
}

void GameObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	painter->save();
	painter->setPen(pen());
	painter->setBrush(brush());
	painter->setClipping(true);
	painter->setClipRect(option->rect);
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawPath(path());

#ifdef DEBUG
	painter->setPen(QPen(Qt::red, 1));
	painter->setBrush(Qt::transparent);
	painter->drawRect(boundingRect());
#endif
	painter->restore();
}
