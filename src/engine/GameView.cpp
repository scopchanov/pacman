#include "GameView.h"

GameView::GameView(QWidget *parent) :
	QGraphicsView{parent}
{
	setCursor(Qt::BlankCursor);
	setAlignment(Qt::AlignCenter);
	setFrameStyle(QFrame::NoFrame);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setBackgroundBrush(QBrush(Qt::black));
	setSceneRect(0, 0, 720, 768);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void GameView::wheelEvent(QWheelEvent *event)
{

}
