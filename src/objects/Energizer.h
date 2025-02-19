#ifndef ENERGIZER_H
#define ENERGIZER_H

#include "GameObject.h"

class Energizer : public GameObject
{
public:
	explicit Energizer(GameObject *parent = nullptr);

	int objectType() const override;
};

#endif // ENERGIZER_H
