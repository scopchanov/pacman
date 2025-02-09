#include "Ghost.h"
#include "GhostEye.h"
#include "PathBuilder.h"
#include <QPen>

Ghost::Ghost(GameObject *parent) :
	Enemy(parent),
	_leftEye{new GhostEye(this)},
	_rightEye{new GhostEye(this)}
{
	_leftEye->setPos(-6, -6);
	_rightEye->setPos(6, -6);

	setPath(PathBuilder::enemyPath(0));
	setPen(QPen(Qt::transparent));
}

GhostEye *Ghost::leftEye() const
{
	return _leftEye;
}

GhostEye *Ghost::rightEye() const
{
	return _rightEye;
}

void Ghost::setup(Game *game)
{
	Enemy::setup(game);
}
