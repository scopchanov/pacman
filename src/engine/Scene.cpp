#include "Scene.h"
#include "InputSystem.h"
#include <QKeyEvent>

Scene::Scene(QObject *parent) :
    QGraphicsScene{parent},
    m_inputSystem{new InputSystem}
{

}

InputSystem *Scene::inputSystem() const
{
    return m_inputSystem;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    Vector2 userInput;

    switch (event->key()) {
    case Qt::Key_Left:
        userInput.set(-1, 0);
        break;
    case Qt::Key_Right:
        userInput.set(1, 0);
        break;
    case Qt::Key_Up:
        userInput.set(0, -1);
        break;
    case Qt::Key_Down:
        userInput.set(0, 1);
        break;
    default:
        break;
    }

    m_inputSystem->setUserInput(userInput);
}
