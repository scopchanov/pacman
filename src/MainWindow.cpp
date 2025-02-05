#include "MainWindow.h"
#include "Game.h"
#include "GameController.h"
#include "ScoreDisplay.h"
#include "LifesDisplay.h"
#include "engine/Scene.h"
#include "engine/GameView.h"
#include "FileHandler.h"
#include <QJsonObject>
#include <QBoxLayout>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent)
{
	auto *layoutMain{new QVBoxLayout(this)};
	auto *layoutPanel{new QHBoxLayout()};
	auto *gameView{new GameView(this)};
	auto *scannerView{new GameView(this)};
	auto *scoreDisplay{new ScoreDisplay(this)};
	auto *lifesDisplay{new LifesDisplay(this)};
	auto *game{new Game(this)};

	gameView->setScene(game->scene());
	gameView->scale(3, 3);
	gameView->centerOn(360, 588);

	scannerView->setScene(game->scene());
	scannerView->scale(0.25, 0.25);
	scannerView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

	layoutPanel->addWidget(scoreDisplay);
	layoutPanel->addWidget(scannerView);
	layoutPanel->addWidget(lifesDisplay);
	layoutPanel->setContentsMargins(100, 0, 0, 0);
	layoutPanel->setSpacing(0);

	layoutMain->addWidget(gameView);
	layoutMain->addLayout(layoutPanel);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	connect(game->gameController(), &GameController::lifesLeftChanged,
			lifesDisplay, &LifesDisplay::setLifeCount);
	connect(game->gameController(), &GameController::scoreChanged,
			scoreDisplay, &ScoreDisplay::setScore);

	showFullScreen();

	game->configure(FileHandler::readFile(":/txt/config.json"));
	game->start();
}
