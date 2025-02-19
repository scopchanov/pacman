#ifndef POKING_H
#define POKING_H

#include "AbstractPersonality.h"

class Poking : public AbstractPersonality
{
public:
	explicit Poking(GameObject *parent = nullptr);

	int type() const override;

	Vector2 calculateTarget() const override;
};

#endif // POKING_H
