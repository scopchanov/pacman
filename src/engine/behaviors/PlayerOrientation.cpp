#include "PlayerOrientation.h"
#include "CharacterMovement.h"
#include "engine/GameObject.h"
#include <QHash>

PlayerOrientation::PlayerOrientation(GameObject *parent) :
	AbstractBehavior(parent),
	m_movement{nullptr}
{

}

void PlayerOrientation::setMovement(CharacterMovement *movement)
{
	m_movement = movement;
}

int PlayerOrientation::type() const
{
	return BT_PlayerOrientation;
}

void PlayerOrientation::performActions()
{
	if (!m_movement)
		return;

	parent()->setRotation(directionToAngle(m_movement->direction()));
}

qreal PlayerOrientation::directionToAngle(const Vector2 &direction) const
{
	return QHash<Vector2, int>{{Vector2(-1, 0), 0},
							   {Vector2(1, 0), 180},
							   {Vector2(0, -1), 90},
							   {Vector2(0, 1), 270}}.value(direction);
}
