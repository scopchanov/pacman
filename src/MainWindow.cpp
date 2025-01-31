#include "MainWindow.h"
#include "Game.h"
#include "engine/Scene.h"
#include "FileHandler.h"
#include <QJsonObject>
#include <QBoxLayout>
#include <QGraphicsView>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    auto *layoutMain{new QVBoxLayout(this)};
    auto *gameView{new QGraphicsView(this)};
    auto *game{new Game(this)};

	gameView->setScene(game->scene());
	gameView->setAlignment(Qt::AlignCenter);
    gameView->setSceneRect(0, 0, 720, 792);
    gameView->setFrameStyle(QFrame::NoFrame);
    gameView->setBackgroundBrush(QBrush(Qt::black));
    // gameView->scale(0.5, 0.5);

    layoutMain->addWidget(gameView);
    layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	resize(730, 820);
	showFullScreen();

	if (game->config(FileHandler::readFile(":/txt/config.json")))
		game->start();
}
