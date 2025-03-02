#ifndef LEVELMODE_H
#define LEVELMODE_H

#include "AbstractGameObject.h"

class LevelMode : public AbstractGameObject
{
public:
	explicit LevelMode(AbstractGameObject *parent = nullptr);

	int step() const;
	void setStep(int step);
	void incrementStep();
	int objectType() const override;	

private:
	int _step;
};

#endif // LEVELMODE_H
