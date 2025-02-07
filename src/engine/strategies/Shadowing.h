#ifndef SHADOWING_H
#define SHADOWING_H

#include "AbstractChasingStrategy.h"

class Shadowing : public AbstractChasingStrategy
{
public:
	explicit Shadowing();

	Vector2 calculateTargetPosition() const override;
};

#endif // SHADOWING_H
