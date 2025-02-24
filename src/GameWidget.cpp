#include "GameWidget.h"
#include "Configurator.h"
#include "FileHandler.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "Palette.h"
#include "GameView.h"
#include "LifesDisplay.h"
#include "ScoreDisplay.h"
#include "Game.h"
#include "GameStatus.h"
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

	layoutPanel->addWidget(scoreDisplay);
	layoutPanel->addWidget(lifesDisplay);
	layoutPanel->setContentsMargins(0, 20, 0, 20);
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
	Configurator configurator;

	Game::ref().newGame();

	configurator.configure(FileHandler::readFile(":/txt/config.json"));

	_gameView->setScene(Game::ref().level());
	_gameView->setSceneRect(0, 0, 720, 792);
	_gameView->setBackgroundBrush(Game::ref().palette()->color(CR_Background));
	_gameView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	Game::ref().start();
}
