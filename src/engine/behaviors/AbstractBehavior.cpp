#include "AbstractBehavior.h"

AbstractBehavior::AbstractBehavior(GameObject *parent) :
	m_parent{parent}
{

}

GameObject *AbstractBehavior::parent() const
{
	return m_parent;
}

void AbstractBehavior::setParent(GameObject *parent)
{
	m_parent = parent;
}

void AbstractBehavior::execute()
{
	if (!m_parent)
		return;

	performActions();
}
