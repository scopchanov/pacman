#ifndef LIFESDISPLAY_H
#define LIFESDISPLAY_H

#include <QWidget>

class LifesDisplay : public QWidget
{
	Q_OBJECT
public:
	explicit LifesDisplay(QWidget *parent = nullptr);

	void setLifeCount(int value);
};

#endif // LIFESDISPLAY_H
