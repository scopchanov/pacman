#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class AbstractPersonality;

class Enemy : public Character
{
public:
	explicit Enemy(GameObject *parent = nullptr);
	~Enemy();

	AbstractPersonality *personality() const;
	void setPersonality(AbstractPersonality *personality);

	void setup(Game *game) override;

private:
	AbstractPersonality *_personality;
};

#endif // ENEMY_H
