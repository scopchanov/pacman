#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character
{
public:
	explicit Enemy(GameObject *parent = nullptr);

	void setup(Game *game) override;
};

#endif // ENEMY_H
