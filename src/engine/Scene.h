#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class InputSystem;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    InputSystem *inputSystem() const;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    InputSystem *m_inputSystem;

signals:
	void pauseGame();
	void resumeGame();
};

#endif // SCENE_H
