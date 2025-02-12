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

	Game *game() const;

private:
	Game *_game;
	GameView *_gameView;

signals:
	void gameOver();
};

#endif // GAMEWIDGET_H
