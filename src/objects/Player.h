#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character
{
public:
	explicit Player(AbstractGameObject *parent = nullptr);
	
	void energize();
	void deenergize();

	int objectType() const override final;

private:
	void enableEnemyEating(bool enable);
};

#endif // PLAYER_H
