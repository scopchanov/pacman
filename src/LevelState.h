#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "AbstractGameObject.h"

class LevelState : public AbstractGameObject
{
public:
	explicit LevelState(AbstractGameObject *parent = nullptr);

	int objectType() const override;
};

#endif // LEVELSTATE_H
