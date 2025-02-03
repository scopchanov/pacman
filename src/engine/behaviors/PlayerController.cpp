#include "PlayerController.h"
#include "engine/InputSystem.h"
#include "CharacterMovement.h"

PlayerController::PlayerController(GameObject *parent) :
	AbstractBehavior(parent),
	m_inputSystem{nullptr},
	m_characterMovement{nullptr}
{

}

void PlayerController::setInputSystem(InputSystem *inputSystem)
{
	m_inputSystem = inputSystem;
}

void PlayerController::setCharacterMovement(CharacterMovement *characterMovement)
{
	m_characterMovement = characterMovement;
}

int PlayerController::type() const
{
	return BT_PlayerController;
}

void PlayerController::performActions()
{
	if (!m_inputSystem || !m_characterMovement)
		return;

	Vector2 userInput{m_inputSystem->userInput()};

	if (userInput.x() || userInput.y())
		m_characterMovement->setNextMove(userInput);
}
