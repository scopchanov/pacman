#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Game;

class Character : public GameObject
{
public:
	explicit Character(GameObject *parent = nullptr);

	virtual void setup(Game *game) = 0;
};

#endif // CHARACTER_H
