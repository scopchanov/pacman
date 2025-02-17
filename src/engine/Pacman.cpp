#include "Pacman.h"
#include "PathBuilder.h"
#include "engine/behaviors/CharacterMovement.h"
#include <QPen>

Pacman::Pacman(GameObject *parent) :
	Player(parent)
{
	setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Player, 45));
	setPen(QPen(Qt::transparent));
	setBrush(Qt::white);
}

void Pacman::setup()
{
	Player::setup();

	auto *behavior{findBehavior(AbstractBehavior::BT_CharacterMovement)};
	auto *movement{static_cast<CharacterMovement *>(behavior)};

	movement->setSpeed(181.818183);
	movement->setNextDirection(V2_LEFT);
}
