#ifndef DEBUG_H
#define DEBUG_H

#include "AbstractBehavior.h"

class CharacterMovement;

class Debug : public AbstractBehavior
{
public:
	explicit Debug(GameObject *parent = nullptr);
	
	void setMovement(CharacterMovement *movement);
	int type() const override;

private:
	void performActions() override;

	CharacterMovement *m_movement;
};

#endif // DEBUG_H
