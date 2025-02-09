#ifndef GHOST_H
#define GHOST_H

#include "Enemy.h"

class GhostEye;

class Ghost : public Enemy
{
public:
	explicit Ghost(GameObject *parent = nullptr);

	GhostEye *leftEye() const;
	GhostEye *rightEye() const;

	void setup(Game *game) override;

private:
	GhostEye *_leftEye;
	GhostEye *_rightEye;
};

#endif // GHOST_H
