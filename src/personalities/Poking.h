#ifndef POKING_H
#define POKING_H

#include "AbstractPersonality.h"

class Poking : public AbstractPersonality
{
public:
	explicit Poking(AbstractGameObject *parent = nullptr);

	int type() const override;

	Vector2 calculateTarget() const override;
};

#endif // POKING_H
