#include "AnimateTeleporter.h"

AnimateTeleporter::AnimateTeleporter(AbstractComponent *parent) :
	AbstractAnimate(parent)
{
	setFrameRate(2);
}

void AnimateTeleporter::reset()
{
	setValue(0);
	updateParent();
}

void AnimateTeleporter::update()
{
	if (value() >= 360)
		setValue(0);
}
