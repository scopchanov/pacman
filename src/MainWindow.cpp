#include "MainWindow.h"
#include "Game.h"
#include "engine/Scene.h"
#include "FileHandler.h"
#include <QJsonObject>
#include <QBoxLayout>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent)
{
	auto *layoutMain{new QHBoxLayout(this)};
	auto *gameView{new QGraphicsView(this)};
	auto *scannerView{new QGraphicsView(this)};
	auto *game{new Game(this)};

	gameView->setScene(game->scene());
	gameView->setAlignment(Qt::AlignCenter);
	gameView->setSceneRect(0, 0, 720, 792);
	gameView->setFrameStyle(QFrame::NoFrame);
	gameView->setBackgroundBrush(QBrush(Qt::black));
	// gameView->scale(3, 3);
	gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	gameView->centerOn(360, 588);

	scannerView->setScene(game->scene());
	scannerView->setAlignment(Qt::AlignCenter);
	scannerView->setSceneRect(0, 0, 720, 792);
	scannerView->setFrameStyle(QFrame::NoFrame);
	scannerView->setBackgroundBrush(QBrush(0x424242));
	scannerView->scale(0.25, 0.25);
	scannerView->resize(300, 300);

	layoutMain->addWidget(gameView);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	resize(730, 820);
	showFullScreen();

	if (game->configure(FileHandler::readFile(":/txt/config.json")))
		game->start();
}
