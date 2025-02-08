#include "MainWindow.h"
#include "ScoreDisplay.h"
#include "LifesDisplay.h"
#include "engine/GameEngine.h"
#include "engine/GameController.h"
#include "engine/GameScene.h"
#include "engine/GameView.h"
#include "FileHandler.h"
#include <QJsonObject>
#include <QBoxLayout>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent)
{
	auto *layoutMain{new QHBoxLayout(this)};
	auto *layoutMiddle{new QVBoxLayout()};
	auto *layoutPanel{new QHBoxLayout()};
	auto *gameView{new GameView(this)};
	auto *scoreDisplay{new ScoreDisplay(this)};
	auto *lifesDisplay{new LifesDisplay(this)};
	auto *game{new GameEngine(this)};

	gameView->setScene(game->scene());

	layoutPanel->addWidget(scoreDisplay);
	layoutPanel->addWidget(lifesDisplay);
	layoutPanel->setContentsMargins(0, 0, 0, 0);
	layoutPanel->setSpacing(0);

	layoutMiddle->addStretch();
	layoutMiddle->addLayout(layoutPanel);
	layoutMiddle->addWidget(gameView);
	layoutMiddle->addStretch();
	layoutMiddle->setContentsMargins(0, 0, 0, 0);
	layoutMiddle->setSpacing(0);

	layoutMain->addStretch();
	layoutMain->addLayout(layoutMiddle);
	layoutMain->addStretch();
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
