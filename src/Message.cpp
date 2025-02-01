#include "Message.h"
#include <QFont>

Message::Message(QGraphicsItem *parent) :
	QGraphicsTextItem{parent}
{
	setDefaultTextColor(0xFBC02D);
	setFont(QFont("Neucha", 18, QFont::Bold, false));
}

QPointF Message::basePosition() const
{
	return m_basePosition;
}

void Message::setBasePosition(qreal x, qreal y)
{
	m_basePosition = QPointF(x, y);
}

void Message::setText(const QString &str)
{
	setPlainText(str);
	setPos(m_basePosition.x() - boundingRect().width()/2.0,
		   m_basePosition.y() - boundingRect().height()/2.0);
}
