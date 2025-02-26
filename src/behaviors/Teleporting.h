#ifndef TELEPORTING_H
#define TELEPORTING_H

#include "AbstractBehavior.h"

class Teleporting : public AbstractBehavior
{
public:
	explicit Teleporting(AbstractComponent *parent = nullptr);

	int type() const override;
};

#endif // TELEPORTING_H
