#ifndef ANIMATEENERGIZER_H
#define ANIMATEENERGIZER_H

#include "AbstractAnimate.h"

class AnimateEnergizer : public AbstractAnimate
{
public:
	explicit AnimateEnergizer(AbstractComponent *parent = nullptr);

	void reset() override;

private:
	void update() override;
};

#endif // ANIMATEENERGIZER_H
