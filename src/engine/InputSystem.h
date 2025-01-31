#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <QObject>
#include "Vector2.h"

class InputSystem : public QObject
{
    Q_OBJECT
public:
    explicit InputSystem(QObject *parent = nullptr);

    Vector2 userInput() const;
    void setUserInput(const Vector2 &vector);

private:
    Vector2 m_userInput;
};

#endif // INPUTSYSTEM_H
