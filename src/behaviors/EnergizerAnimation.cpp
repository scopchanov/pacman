#include "EnergizerAnimation.h"
#include "PathBuilder.h"

EnergizerAnimation::EnergizerAnimation(GameObject *parent) :
	AbstractAnimationBehavior(parent)
{
	setValue(0);
	setFrameRate(15);
	setPathType(PathBuilder::GO_Energizer);
}

void EnergizerAnimation::update()
{
	if (value() > 8)
		setValue(0);
}
