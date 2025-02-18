#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "engine/objects/GameObject.h"

class Teleporter : public GameObject
{
public:
	explicit Teleporter(GameObject *parent = nullptr);

	void setup(const QPointF &src, const QPointF &dst);
};

#endif // TELEPORTER_H
