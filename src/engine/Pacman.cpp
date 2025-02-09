#include "Pacman.h"
#include "PathBuilder.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/PlayerAnimation.h"
#include <QPen>

Pacman::Pacman(GameObject *parent) :
	Player(parent)
{
	setPath(PathBuilder::playerPath(45));
	setPen(QPen(Qt::transparent));
	setBrush(Qt::white);
}

void Pacman::setup(Game *game)
{
	Player::setup(game);

	auto *behavior{findBehavior(AbstractBehavior::BT_CharacterMovement)};
	auto *movement{static_cast<CharacterMovement *>(behavior)};

	movement->setMovingSpeed(200);
	movement->setNextDirection(Vector2(-1, 0));

	behavior = findBehavior(AbstractBehavior::BT_Animation);
	auto *animation{static_cast<PlayerAnimation *>(behavior)};

	animation->setFrameTime(150);
}
