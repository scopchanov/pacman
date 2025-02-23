#ifndef SPEEDING_H
#define SPEEDING_H

#include "AbstractPersonality.h"

class Speeding : public AbstractPersonality
{
public:
	explicit Speeding(AbstractGameObject *parent = nullptr);

	int type() const override;

	Vector2 calculateTarget() const override;
};

#endif // SPEEDING_H
