#include "GameWidget.h"
#include "LifesDisplay.h"
#include "ScoreDisplay.h"
#include "engine/Game.h"
#include "engine/GameStatus.h"
#include "engine/GameView.h"
#include "Configurator.h"
#include "FileHandler.h"
#include <QJsonObject>
#include <QBoxLayout>

GameWidget::GameWidget(QWidget *parent) :
	QWidget{parent},
	_gameView{new GameView(this)}
{
	auto *layoutMain{new QHBoxLayout(this)};
	auto *layoutMiddle{new QVBoxLayout()};
	auto *layoutPanel{new QHBoxLayout()};
	auto *scoreDisplay{new ScoreDisplay(this)};
	auto *lifesDisplay{new LifesDisplay(this)};

	Configurator configurator;

	configurator.configure(FileHandler::readFile(":/txt/config.json"));

	_gameView->setScene(Game::ref().scene());

	layoutPanel->addWidget(scoreDisplay);
	layoutPanel->addWidget(lifesDisplay);
	layoutPanel->setContentsMargins(36, 0, 36, 0);
	layoutPanel->setSpacing(0);

	layoutMiddle->addStretch();
	layoutMiddle->addLayout(layoutPanel);
	layoutMiddle->addWidget(_gameView);
	layoutMiddle->addStretch();
	layoutMiddle->setContentsMargins(0, 0, 0, 0);
	layoutMiddle->setSpacing(0);

	layoutMain->addStretch();
	layoutMain->addLayout(layoutMiddle);
	layoutMain->addStretch();
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	connect(Game::ref().status(), &GameStatus::lifesLeftChanged,
			lifesDisplay, &LifesDisplay::setLifeCount);
	connect(Game::ref().status(), &GameStatus::scoreChanged,
			scoreDisplay, &ScoreDisplay::setScore);

	connect(&Game::ref(), &Game::playerWins, this, &GameWidget::exitGame);
	connect(&Game::ref(), &Game::gameOver, this, &GameWidget::exitGame);
}

void GameWidget::startGame()
{
	Game::ref().start();
}
