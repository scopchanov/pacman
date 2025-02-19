#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character
{
public:
	explicit Player(GameObject *parent = nullptr);
	
	int objectType() const override final;

	void setup() override;
};

#endif // PLAYER_H
