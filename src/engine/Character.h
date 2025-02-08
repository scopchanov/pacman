#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class GameEngine;

class Character : public GameObject
{
public:
	explicit Character(GameObject *parent = nullptr);

	virtual void setup(GameEngine *game) = 0;
};

#endif // CHARACTER_H
