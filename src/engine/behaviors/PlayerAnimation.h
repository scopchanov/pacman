#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include "AbstractAnimationBehavior.h"

class PlayerAnimation : public AbstractAnimationBehavior
{
public:
	explicit PlayerAnimation(GameObject *parent = nullptr);

	void reset() override;

private:
	void update() override;
};

#endif // PLAYERANIMATION_H
