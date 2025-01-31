#include "InputSystem.h"

InputSystem::InputSystem(QObject *parent) :
    QObject{parent}
{

}

Vector2 InputSystem::userInput() const
{
    return m_userInput;
}

void InputSystem::setUserInput(const Vector2 &vector)
{
    m_userInput = vector;
}
