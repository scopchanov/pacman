#include "InputSystem.h"

InputSystem::InputSystem(QObject *parent) :
	QObject{parent}
{

}

Vector2 InputSystem::userInput() const
{
	return _userInput;
}

void InputSystem::setUserInput(const Vector2 &vector)
{
	_userInput = vector;
}
