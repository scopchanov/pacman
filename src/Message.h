#ifndef MESSAGE_H
#define MESSAGE_H

#include <QGraphicsTextItem>

class Message : public QGraphicsTextItem
{
public:
	explicit Message(QGraphicsItem *parent = nullptr);

	QPointF basePosition() const;
	void setBasePosition(qreal x, qreal y);

	void setText(const QString &str);

private:
	QPointF m_basePosition;
};

#endif // MESSAGE_H
