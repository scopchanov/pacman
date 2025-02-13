#include "MainWindow.h"
#include "GameWidget.h"
#include "GameMenu.h"

MainWindow::MainWindow(QWidget *parent) :
	QStackedWidget(parent),
	_gameMenu{new GameMenu(this)},
	_gameWidget{new GameWidget(this)}
{
	addWidget(_gameMenu);
	addWidget(_gameWidget);
	setCurrentWidget(_gameMenu);
	showFullScreen();

	connect(_gameMenu, &GameMenu::newGame, this, &MainWindow::onNewGame);
	connect(_gameWidget, &GameWidget::exitGame, this, &MainWindow::onGameOver);
}

void MainWindow::onNewGame()
{
	setCurrentWidget(_gameWidget);
	_gameWidget->startGame();
}

void MainWindow::onGameOver()
{
	setCurrentWidget(_gameMenu);
}
