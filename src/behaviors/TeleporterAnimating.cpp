#include "TeleporterAnimating.h"

TeleporterAnimating::TeleporterAnimating(AbstractGameObject *parent) :
	AbstractAnimatingBehavior(parent)
{
	setFrameRate(150);
}

void TeleporterAnimating::reset()
{
	setValue(45);
	setDirection(DIR_Forwards);
	updateParent();
}

void TeleporterAnimating::update()
{
	if (value() > 45)
		setValue(0);
}
