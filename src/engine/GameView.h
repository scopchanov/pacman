#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

class GameView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit GameView(QWidget *parent = nullptr);

protected:
	void wheelEvent(QWheelEvent *) override;
};

#endif // GAMEVIEW_H
