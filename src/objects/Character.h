#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
public:
	explicit Character(GameObject *parent = nullptr);

	void setSpeed(qreal percent);
};

#endif // CHARACTER_H
