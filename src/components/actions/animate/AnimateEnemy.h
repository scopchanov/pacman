#ifndef ANIMATEENEMY_H
#define ANIMATEENEMY_H

#include "AbstractAnimate.h"

class AnimateEnemy : public AbstractAnimate
{
public:
	explicit AnimateEnemy(AbstractComponent *parent = nullptr);

	void reset() override;

private:
	void update() override;
};

#endif // ANIMATEENEMY_H
