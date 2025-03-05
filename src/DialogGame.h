#ifndef DIALOGGAME_H
#define DIALOGGAME_H

#include <QDialog>

class DialogGame : public QDialog
{
	Q_OBJECT
public:
	explicit DialogGame(QWidget *parent = nullptr);
};

#endif // DIALOGGAME_H
