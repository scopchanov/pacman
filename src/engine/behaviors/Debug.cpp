#include "Debug.h"
#include "engine/GameObject.h"
#include "engine/behaviors/CharacterMovement.h"

Debug::Debug(GameObject *parent) :
	AbstractBehavior(parent),
	m_movement{nullptr}
{

}

void Debug::setMovement(CharacterMovement *movement)
{
	m_movement = movement;
}

int Debug::type() const
{
	return BT_Debug;
}

void Debug::performActions()
{
	if (!m_movement)
		return;

	parent()->setPos(m_movement->parent()->mapFromScene(m_movement->targetPosition().toPointF()));
}
