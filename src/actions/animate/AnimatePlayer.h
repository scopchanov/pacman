#ifndef ANIMATEPLAYER_H
#define ANIMATEPLAYER_H

#include "AbstractAnimate.h"

class AnimatePlayer : public AbstractAnimate
{
public:
	explicit AnimatePlayer(AbstractComponent *parent = nullptr);

	void reset() override;

private:
	void update() override;
};

#endif // ANIMATEPLAYER_H
