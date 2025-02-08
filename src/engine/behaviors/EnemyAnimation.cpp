#include "EnemyAnimation.h"
#include "PathBuilder.h"
#include "engine/GameObject.h"
#include "engine/GameTimer.h"

EnemyAnimation::EnemyAnimation(GameObject *parent) :
	AbstractTimedBehavior(parent),
	_value{0},
	_n{1}
{

}

int EnemyAnimation::type() const
{
	return BT_EnemyAnimation;
}

void EnemyAnimation::reset()
{

}

void EnemyAnimation::performTimedActions()
{
	_value += _n*20*gameTimer()->deltaTime();

	if (_value > 2) {
		_value = 2;
		_n = -1;
	}


	if (_value < -2) {
		_value = -2;
		_n = 1;
	}

	parent()->setPath(PathBuilder::enemyPath(_value));
}
