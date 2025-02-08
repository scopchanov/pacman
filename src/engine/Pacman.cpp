#include "Pacman.h"
#include "PathBuilder.h"
#include "engine/behaviors/CharacterMovement.h"
#include <QPen>

Pacman::Pacman(GameObject *parent) :
	Player(parent)
{
	setPath(PathBuilder::playerPath(45));
	setPen(QPen(Qt::transparent));
	setBrush(Qt::white);
	setPos(360, 588);

	movement()->setMovingSpeed(200);
	movement()->setNextDirection(Vector2(-1, 0));
	movement()->reset();
}
