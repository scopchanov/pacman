#ifndef SCATTERINDICATOR_H
#define SCATTERINDICATOR_H

#include <QWidget>

class ScatterIndicator : public QWidget
{
	Q_OBJECT
public:
	explicit ScatterIndicator(QWidget *parent = nullptr);

	void turnOn();
	void turnOff();
	QSize sizeHint() const override;

protected:
	void paintEvent(QPaintEvent *event) override;
};

#endif // SCATTERINDICATOR_H
