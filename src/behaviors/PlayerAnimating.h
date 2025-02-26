#ifndef PLAYERANIMATING_H
#define PLAYERANIMATING_H

#include "AbstractAnimatingBehavior.h"

class PlayerAnimating : public AbstractAnimatingBehavior
{
public:
	explicit PlayerAnimating(AbstractComponent *parent = nullptr);

	void reset() override;

private:
	void update() override;
};

#endif // PLAYERANIMATING_H
