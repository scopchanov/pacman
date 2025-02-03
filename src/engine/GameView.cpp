#include "GameView.h"

GameView::GameView(QWidget *parent) :
	QGraphicsView{parent}
{
	setCursor(Qt::BlankCursor);
}

void GameView::wheelEvent(QWheelEvent *event)
{

}
