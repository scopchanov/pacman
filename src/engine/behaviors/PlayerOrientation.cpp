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

void PlayerOrientation::reset()
{

}

void PlayerOrientation::performActions()
{
	if (!m_movement)
		return;

	parent()->setRotation(directionToAngle(m_movement->currentDirection()));
}

qreal PlayerOrientation::directionToAngle(const Vector2 &direction) const
{
	if (direction == Vector2(-1, 0))
		return 0;
	else if (direction == Vector2(1, 0))
		return 180;
	else if (direction == Vector2(0, -1))
		return 90;
	else
		return 270;

	// return QHash<Vector2, int>{{Vector2(-1, 0), 0},
	// 						   {Vector2(1, 0), 180},
	// 						   {Vector2(0, -1), 90},
	// 						   {Vector2(0, 1), 270}}.value(direction);
}
