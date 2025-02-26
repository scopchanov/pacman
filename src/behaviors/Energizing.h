#ifndef ENERGIZING_H
#define ENERGIZING_H

#include "AbstractBehavior.h"

class Energizing : public AbstractBehavior
{
public:
	explicit Energizing(AbstractComponent *parent = nullptr);

	int type() const override;
};

#endif // ENERGIZING_H
