#ifndef POWERUPANIMATION_H
#define POWERUPANIMATION_H

#include "AbstractAnimationBehavior.h"

class PowerUpAnimation : public AbstractAnimationBehavior
{
public:
	explicit PowerUpAnimation(GameObject *parent = nullptr);

private:
	void update() override;
};

#endif // POWERUPANIMATION_H
