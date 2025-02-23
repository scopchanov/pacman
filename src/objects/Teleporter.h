#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "AbstractGameObject.h"

class Teleporter : public AbstractGameObject
{
public:
	explicit Teleporter(AbstractGameObject *parent = nullptr);

	int objectType() const override final;
};

#endif // TELEPORTER_H
