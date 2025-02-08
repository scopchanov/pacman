#include "PlayerAnimation.h"
#include "PathBuilder.h"
#include "engine/GameObject.h"
#include "engine/GameTimer.h"

PlayerAnimation::PlayerAnimation(GameObject *parent) :
	AbstractTimedBehavior(parent),
	m_angle{0}
{

}

int PlayerAnimation::type() const
{
	return BT_PlayerAnimation;
}

void PlayerAnimation::reset()
{

}

void PlayerAnimation::performTimedActions()
{
	m_angle += 150*gameTimer()->deltaTime();

	if (m_angle >= 45)
		m_angle = 0;

	parent()->setPath(PathBuilder::playerPath(m_angle));
}
