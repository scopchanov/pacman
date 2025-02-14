#include "EnergizerAnimation.h"
#include "PathBuilder.h"

EnergizerAnimation::EnergizerAnimation(GameObject *parent) :
	AbstractAnimationBehavior(parent)
{
	setValue(8);
	setFrameRate(15);
	setGameObjectType(PathBuilder::GO_Energizer);
}

void EnergizerAnimation::update()
{
	if (value() > 16)
		setValue(8);
}
