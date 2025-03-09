#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

class Game;
class GameView;
class ProgressBar;
class ScatterIndicator;

class GameWidget : public QWidget
{
	Q_OBJECT
public:
	explicit GameWidget(QWidget *parent = nullptr);

	void startGame();

private:
	GameView *_gameView;
	ProgressBar *_progressLeft;
	ProgressBar *_progressRight;
	ScatterIndicator *_scatterIndicator;

private slots:
	void onLevelModeChanged();
	void onPauseGame();

signals:
	void pauseGame();
	void exitGame();
};

#endif // GAMEWIDGET_H
