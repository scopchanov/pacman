#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character
{
public:
	explicit Enemy(GameObject *parent = nullptr);
};

#endif // ENEMY_H
