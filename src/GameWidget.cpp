#include "GameWidget.h"
#include "Configurator.h"
#include "DialogGame.h"
#include "FileHandler.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "Palette.h"
#include "GameView.h"
#include "LifesDisplay.h"
#include "ScoreDisplay.h"
#include "Game.h"
#include "GameStatus.h"
#include "ui/ProgressBar.h"
#include "ui/ScatterIndicator.h"
#include <QJsonObject>
#include <QBoxLayout>

GameWidget::GameWidget(QWidget *parent) :
	QWidget{parent},
	_gameView{new GameView(this)},
	_progressLeft{new ProgressBar(this)},
	_progressRight{new ProgressBar(this)},
	_scatterIndicator{new ScatterIndicator(this)}
{
	auto *layoutMain{new QHBoxLayout(this)};
	auto *layoutMiddle{new QVBoxLayout()};
	auto *layoutGame{new QHBoxLayout()};
	auto *layoutPanel{new QHBoxLayout()};
	auto *scoreDisplay{new ScoreDisplay(this)};
	auto *lifesDisplay{new LifesDisplay(this)};

	layoutPanel->addWidget(scoreDisplay);
	layoutPanel->addWidget(_scatterIndicator);
	layoutPanel->addWidget(lifesDisplay);
	layoutPanel->setContentsMargins(0, 20, 0, 20);
	layoutPanel->setSpacing(0);

	layoutGame->addWidget(_progressLeft);
	layoutGame->addWidget(_gameView);
	layoutGame->addWidget(_progressRight);
	layoutGame->setContentsMargins(0, 0, 0, 0);
	layoutGame->setSpacing(10);

	layoutMiddle->addStretch();
	layoutMiddle->addLayout(layoutPanel);
	layoutMiddle->addLayout(layoutGame);
	layoutMiddle->addStretch();

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

	connect(Game::ref().level(), &GameLevel::escapePressed, this, &GameWidget::onPauseGame);
	connect(Game::ref().level(), &GameLevel::energizedProgressChanged,
			_progressLeft, &ProgressBar::setValue);
	connect(Game::ref().level(), &GameLevel::energizedProgressChanged,
			_progressRight, &ProgressBar::setValue);

	Game::ref().start();
}

void GameWidget::onPauseGame()
{
	DialogGame dlg(_gameView->viewport());
	QColor color{Qt::black};

	color.setAlphaF(0.5);

	Game::ref().stop();

	_gameView->setForegroundBrush(color);

	if (dlg.exec() == QDialog::Rejected)
		Game::ref().resume();
	else
		emit exitGame();

	_gameView->setForegroundBrush(QBrush());
}
