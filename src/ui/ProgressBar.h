#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>

class ProgressBar : public QWidget
{
	Q_OBJECT
public:
	explicit ProgressBar(QWidget *parent = nullptr);

	void setValue(qreal value);
	QSize sizeHint() const override;

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	qreal _value;
};

#endif // PROGRESSBAR_H
