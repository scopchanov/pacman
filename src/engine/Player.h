#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character
{
public:
	explicit Player(GameObject *parent = nullptr);
	
	void setup() override;
};

#endif // PLAYER_H
