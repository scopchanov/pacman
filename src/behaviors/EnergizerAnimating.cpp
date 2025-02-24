#include "EnergizerAnimating.h"

EnergizerAnimating::EnergizerAnimating(AbstractGameObject *parent) :
	AbstractAnimatingBehavior(parent)
{
	setValue(0);
	setFrameRate(15);
}

void EnergizerAnimating::reset()
{
	setValue(8);
	updateParent();
}

void EnergizerAnimating::update()
{
	if (value() > 8)
		setValue(0);
}
