#include "Message.h"
#include <QFont>

Message::Message(QGraphicsItem *parent) :
	QGraphicsTextItem{parent}
{
	setDefaultTextColor(0xFFC107);
	setFont(QFont("Neucha", 26, QFont::Bold, false));
}

QPointF Message::basePosition() const
{
	return _basePosition;
}

void Message::setBasePosition(qreal x, qreal y)
{
	_basePosition = QPointF(x, y);
}

void Message::setText(const QString &str)
{
	setPlainText(str);
	setPos(_basePosition.x() - boundingRect().width()/2.0,
		   _basePosition.y() - boundingRect().height()/2.0);
}
