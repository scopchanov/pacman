#include "PlayerControlling.h"
#include "Game.h"
#include "GameLevel.h"
#include "InputSystem.h"
#include "Moving.h"

PlayerControlling::PlayerControlling(AbstractGameObject *parent) :
	AbstractControllingBehavior(parent)
{

}

void PlayerControlling::performControllingActions()
{
	const Vector2 &userInput{Game::ref().level()->inputSystem()->userInput()};

	if (userInput.x() || userInput.y())
		moving()->setNextDirection(userInput);
}
