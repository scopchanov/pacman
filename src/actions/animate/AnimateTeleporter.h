#ifndef ANIMATETELEPORTER_H
#define ANIMATETELEPORTER_H

#include "AbstractAnimate.h"

class AnimateTeleporter : public AbstractAnimate
{
public:
	explicit AnimateTeleporter(AbstractComponent *parent = nullptr);

	void reset() override;

private:
	void update() override;
};

#endif // ANIMATETELEPORTER_H
