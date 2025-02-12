#include "MainWindow.h"
#include "FileHandler.h"
#include "GameWidget.h"
#include "GameMenu.h"
#include "Game.h"
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent) :
	QStackedWidget(parent),
	_gameMenu{new GameMenu(this)},
	_gameWidget{new GameWidget(this)}
{
	_gameWidget->game()->configure(FileHandler::readFile(":/txt/config.json"));

	addWidget(_gameMenu);
	addWidget(_gameWidget);
	setCurrentWidget(_gameMenu);
	showFullScreen();

	connect(_gameMenu, &GameMenu::newGame, this, &MainWindow::onNewGame);
	connect(_gameWidget, &GameWidget::gameOver, this, &MainWindow::onGameOver);
}

void MainWindow::onNewGame()
{
	setCurrentWidget(_gameWidget);
	_gameWidget->game()->start();
}

void MainWindow::onGameOver()
{
	setCurrentWidget(_gameMenu);
	// _gameWidget->startGame();
}

void MainWindow::openGameMenu()
{
	// GameDialog dlg(this);

	// dlg.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

	// _game->stop();
	// _gameView->setForegroundBrush(QBrush("#80000000"));

	// if (dlg.exec() == QDialog::Rejected) {
	// 	_gameView->setForegroundBrush(QBrush());
	// 	_game->resume();
	// 	return;
	// }

	// _gameView->setForegroundBrush(QBrush());
	// _game->start();

	// _game->restart();
}
