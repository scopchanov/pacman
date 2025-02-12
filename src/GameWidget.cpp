#include "GameWidget.h"
#include "Game.h"
#include "LifesDisplay.h"
#include "ScoreDisplay.h"
#include "engine/GameController.h"
#include "engine/GameScene.h"
#include "engine/GameView.h"
#include <QJsonObject>
#include <QBoxLayout>

GameWidget::GameWidget(QWidget *parent) :
	QWidget{parent},
	_game{new Game(this)},
	_gameView{new GameView(this)}
{
	auto *layoutMain{new QHBoxLayout(this)};
	auto *layoutMiddle{new QVBoxLayout()};
	auto *layoutPanel{new QHBoxLayout()};
	auto *scoreDisplay{new ScoreDisplay(this)};
	auto *lifesDisplay{new LifesDisplay(this)};

	_gameView->setScene(_game->scene());

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

	connect(_game->gameController(), &GameController::lifesLeftChanged,
			lifesDisplay, &LifesDisplay::setLifeCount);
	connect(_game->gameController(), &GameController::scoreChanged,
			scoreDisplay, &ScoreDisplay::setScore);

	connect(_game, &Game::playerWins, this, &GameWidget::gameOver);
	connect(_game, &Game::playerLoses, this, &GameWidget::gameOver);
	// connect(_game->scene(), &GameScene::pauseGame, this, &MainWindow::openGameMenu);
}

Game *GameWidget::game() const
{
	return _game;
}
