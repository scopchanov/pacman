#include "PlayerController.h"
#include "CharacterMovement.h"
#include "GameGlobals.h"
#include "InputSystem.h"

PlayerController::PlayerController(GameObject *parent) :
	AbstractBehavior(parent),
	_inputSystem{nullptr},
	_characterMovement{nullptr}
{

}

void PlayerController::setInputSystem(InputSystem *inputSystem)
{
	_inputSystem = inputSystem;
}

void PlayerController::setCharacterMovement(CharacterMovement *characterMovement)
{
	_characterMovement = characterMovement;
}

int PlayerController::type() const
{
	return BT_PlayerController;
}

void PlayerController::performActions()
{
	if (!_inputSystem || !_characterMovement)
		return;

	Vector2 userInput{_inputSystem->userInput()};

	if (userInput.x() || userInput.y())
		_characterMovement->setNextDirection(userInput);
}
