#ifndef SHADOWING_H
#define SHADOWING_H

#include "AbstractPersonality.h"

class Shadowing : public AbstractPersonality
{
public:
	explicit Shadowing(GameObject *parent = nullptr);

	int type() const override;

	Vector2 calculateTarget() const override;
};

#endif // SHADOWING_H
