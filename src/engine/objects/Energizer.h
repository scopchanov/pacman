#ifndef ENERGIZER_H
#define ENERGIZER_H

#include "GameObject.h"

class Energizer : public GameObject
{
public:
	explicit Energizer(GameObject *parent = nullptr);
};

#endif // ENERGIZER_H
