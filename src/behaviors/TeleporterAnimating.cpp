#include "TeleporterAnimating.h"

TeleporterAnimating::TeleporterAnimating(AbstractComponent *parent) :
	AbstractAnimatingBehavior(parent)
{
	setFrameRate(2);
}

void TeleporterAnimating::reset()
{
	setValue(0);
	updateParent();
}

void TeleporterAnimating::update()
{
	if (value() >= 360)
		setValue(0);
}
