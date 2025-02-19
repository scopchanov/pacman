#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "GameObject.h"

class Teleporter : public GameObject
{
public:
	explicit Teleporter(GameObject *parent = nullptr);

	int objectType() const override final;

	void setup(const QPointF &src, const QPointF &dst);
};

#endif // TELEPORTER_H
