#include "ControlPlayer.h"
#include "Game.h"
#include "GameLevel.h"
#include "InputSystem.h"
#include "components/actions/tilemap/Move.h"

ControlPlayer::ControlPlayer(AbstractComponent *parent) :
	AbstractControl(parent)
{

}

void ControlPlayer::control()
{
	const Vector2 &userInput{Game::ref().level()->inputSystem()->userInput()};

	if (userInput.x() || userInput.y())
		move()->setNextDirection(userInput);
}
