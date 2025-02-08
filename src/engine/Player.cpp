#include "Player.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/DotsEating.h"
#include "engine/behaviors/PlayerAnimation.h"
#include "engine/behaviors/PlayerController.h"
#include "engine/behaviors/PlayerOrientation.h"

Player::Player(GameObject *parent) :
	Character(parent)
{
	auto *playerController{new PlayerController(this)};
	auto *movement{new CharacterMovement(this)};
	auto *orientation{new PlayerOrientation(this)};

	playerController->setCharacterMovement(movement);
	orientation->setMovement(movement);

	addBehavior(playerController);
	addBehavior(movement);
	addBehavior(orientation);
	addBehavior(new DotsEating(this));
	addBehavior(new PlayerAnimation(this));
}

PlayerController *Player::playerController() const
{
	return static_cast<PlayerController *>(behavior(0));
}

CharacterMovement *Player::movement() const
{
	return static_cast<CharacterMovement *>(behavior(1));
}

DotsEating *Player::dotsEating() const
{
	return static_cast<DotsEating *>(behavior(3));
}

PlayerAnimation *Player::animation() const
{
	return static_cast<PlayerAnimation *>(behavior(4));
}
