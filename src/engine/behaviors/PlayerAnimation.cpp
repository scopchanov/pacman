#include "PlayerAnimation.h"
#include "PathBuilder.h"
#include "engine/GameObject.h"
#include "engine/GameTimer.h"

PlayerAnimation::PlayerAnimation(GameObject *parent) :
	AbstractTimedBehavior(parent),
	_angle{0}
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
	_angle += 150*gameTimer()->deltaTime();

	if (_angle >= 45)
		_angle = 0;

	parent()->setPath(PathBuilder::playerPath(_angle));
}
