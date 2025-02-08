#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class GameTimer;

class Character : public GameObject
{
public:
	explicit Character(GameObject *parent = nullptr);
};

#endif // CHARACTER_H
