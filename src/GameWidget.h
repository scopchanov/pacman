#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

class Game;
class GameView;

class GameWidget : public QWidget
{
	Q_OBJECT
public:
	explicit GameWidget(QWidget *parent = nullptr);

	void startGame();

private:
	Game *_game;
	GameView *_gameView;

signals:
	void exitGame();
};

#endif // GAMEWIDGET_H
