#include "AnimateEnergizer.h"

AnimateEnergizer::AnimateEnergizer(AbstractComponent *parent) :
	AbstractAnimate(parent)
{
	setValue(0);
	setFrameRate(15);
}

void AnimateEnergizer::reset()
{
	setValue(8);
	updateParent();
}

void AnimateEnergizer::update()
{
	if (value() > 8)
		setValue(0);
}
