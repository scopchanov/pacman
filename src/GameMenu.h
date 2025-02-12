#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>

class GameMenu : public QWidget
{
	Q_OBJECT
public:
	explicit GameMenu(QWidget *parent = nullptr);

signals:
	void newGame();
};

#endif // GAMEMENU_H
