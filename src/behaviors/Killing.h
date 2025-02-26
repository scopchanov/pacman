#ifndef KILLING_H
#define KILLING_H

#include "AbstractBehavior.h"

class Killing : public AbstractBehavior
{
public:
	explicit Killing(AbstractComponent *parent = nullptr);

	int type() const override;
};

#endif // KILLING_H
