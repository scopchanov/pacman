#ifndef ENERGIZER_H
#define ENERGIZER_H

#include "AbstractGameObject.h"

class Energizer : public AbstractGameObject
{
public:
	explicit Energizer(AbstractGameObject *parent = nullptr);

	int objectType() const override;
};

#endif // ENERGIZER_H
