#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "AbstractGameObject.h"

class LevelState : public AbstractGameObject
{
public:
	explicit LevelState(AbstractGameObject *parent = nullptr);

	int step() const;
	void setStep(int step);
	void incrementStep();
	int mode() const;
	int objectType() const override;

private:
	int _step;
};

#endif // LEVELSTATE_H
