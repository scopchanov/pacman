#ifndef ABSTRACTINDICATOR_H
#define ABSTRACTINDICATOR_H

#include <QWidget>
#include <QPainterPath>

class AbstractIndicator : public QWidget
{
	Q_OBJECT
public:
	explicit AbstractIndicator(QWidget *parent = nullptr);

	QPen pen() const;
	void setPen(const QPen &pen);
	QBrush brush() const;
	void setBrush(const QBrush &brush);
	QPainterPath path() const;
	void setPath(QPainterPath path);
	QSize sizeHint() const override;

	void turnOn();
	void turnOff();

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	bool _visible;
	QPainterPath _path;
	QPointF _mid;
};

#endif // ABSTRACTINDICATOR_H
