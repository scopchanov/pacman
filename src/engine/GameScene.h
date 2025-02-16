#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class InputSystem;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
	explicit GameScene(QObject *parent = nullptr);

    InputSystem *inputSystem() const;

	void scheduleDelete(QGraphicsItem *item);
	void makeTurn();

	void reset();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
	InputSystem *_inputSystem;
	QList<QGraphicsItem *> _scheduledItems;

signals:
	void pauseGame();
	void resumeGame();
};

#endif // GAMESCENE_H
