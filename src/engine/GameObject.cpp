#include "GameObject.h"
#include "behaviors/AbstractBehavior.h"

GameObject::GameObject(QGraphicsItem *parent) :
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

AbstractBehavior *GameObject::behavior(int n)
{
	return m_behaviors.at(n);
}

void GameObject::advance(int phase)
{
	if (!phase)
		return;

	for (auto *behavior : std::as_const(m_behaviors))
		behavior->execute();
}
