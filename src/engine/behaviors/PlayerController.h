#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "AbstractBehavior.h"

class InputSystem;
class CharacterMovement;

class PlayerController : public AbstractBehavior
{
public:
	explicit PlayerController(GameObject *parent = nullptr);

	void setInputSystem(InputSystem *inputSystem);
	void setCharacterMovement(CharacterMovement *characterMovement);
	int type() const override;

	void reset() override;

private:
	void performActions() override;

	InputSystem *m_inputSystem;
	CharacterMovement *m_characterMovement;
};

#endif // PLAYERCONTROLLER_H
