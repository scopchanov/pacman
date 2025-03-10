#ifndef LIFESDISPLAY_H
#define LIFESDISPLAY_H

#include <QWidget>
#include <QPainterPath>

class LifesDisplay : public QWidget
{
	Q_OBJECT
public:
	explicit LifesDisplay(QWidget *parent = nullptr);

	void setLifeCount(int value);

protected:
	void paintEvent(QPaintEvent *) override;

private:
	int _lifeCount;
	QPainterPath _path;
};

#endif // LIFESDISPLAY_H
