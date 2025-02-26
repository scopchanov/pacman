#ifndef PLAYERCONTROLLING_H
#define PLAYERCONTROLLING_H

#include "AbstractControllingBehavior.h"

class PlayerControlling : public AbstractControllingBehavior
{
public:
	explicit PlayerControlling(AbstractComponent *parent = nullptr);

private:
	void performControllingActions() override;
};

#endif // PLAYERCONTROLLING_H
