#include "TeleporterAnimating.h"

TeleporterAnimating::TeleporterAnimating(AbstractGameObject *parent) :
	AbstractAnimatingBehavior(parent)
{
	setFrameRate(2);
}

void TeleporterAnimating::reset()
{
	setValue(0);
	setDirection(DIR_Forwards);
	updateParent();
}

void TeleporterAnimating::update()
{
	if (value() >= 360)
		setValue(0);
}
