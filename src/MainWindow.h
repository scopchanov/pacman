#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedWidget>

class GameMenu;
class GameWidget;

class MainWindow : public QStackedWidget
{
    Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);

private:
	GameMenu *_gameMenu;
	GameWidget *_gameWidget;

private slots:
	void onNewGame();
	void onGameOver();
};
#endif // MAINWINDOW_H
