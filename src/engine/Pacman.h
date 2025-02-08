#ifndef PACMAN_H
#define PACMAN_H

#include "Player.h"

class Pacman : public Player
{
public:
	explicit Pacman(GameObject *parent = nullptr);

	void setup(Game *game) override;
};

#endif // PACMAN_H
