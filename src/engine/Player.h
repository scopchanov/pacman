#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class PlayerAnimation;
class PlayerController;
class CharacterMovement;
class DotsEating;

class Player : public Character
{
public:
	explicit Player(GameObject *parent = nullptr);

	PlayerController *playerController() const;
	CharacterMovement *movement() const;
	DotsEating *dotsEating() const;
	PlayerAnimation *animation() const;
};

#endif // PLAYER_H
