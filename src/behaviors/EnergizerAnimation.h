#ifndef ENERGIZERANIMATION_H
#define ENERGIZERANIMATION_H

#include "AbstractAnimationBehavior.h"

class EnergizerAnimation : public AbstractAnimationBehavior
{
public:
	explicit EnergizerAnimation(GameObject *parent = nullptr);

private:
	void update() override;
};

#endif // ENERGIZERANIMATION_H
