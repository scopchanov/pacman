#ifndef CHARACTER_H
#define CHARACTER_H

#include "AbstractGameObject.h"

class Character : public AbstractGameObject
{
public:
	explicit Character(AbstractGameObject *parent = nullptr);

	void setSpeed(qreal percent);
};

#endif // CHARACTER_H
