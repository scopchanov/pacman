#include "EnergizerAnimating.h"
#include "PathBuilder.h"

EnergizerAnimating::EnergizerAnimating(GameObject *parent) :
	AbstractAnimatingBehavior(parent)
{
	setValue(0);
	setFrameRate(15);
	setPathType(PathBuilder::GO_Energizer);
}

void EnergizerAnimating::update()
{
	if (value() > 8)
		setValue(0);
}
