#ifndef ABSTRACTORIENTATIONBEHAVIOR_H
#define ABSTRACTORIENTATIONBEHAVIOR_H

#include "AbstractBehavior.h"

class CharacterMovement;

class AbstractOrientationBehavior : public AbstractBehavior
{
public:
	explicit AbstractOrientationBehavior(GameObject *parent = nullptr);

	CharacterMovement *movement() const;
	void setMovement(CharacterMovement *movement);
	int type() const override;

	void reset() override;

private:
	void performActions() override final;
	virtual void performOrientationActions() = 0;

	CharacterMovement *_movement;
};

#endif // ABSTRACTORIENTATIONBEHAVIOR_H
