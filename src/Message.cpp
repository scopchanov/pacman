#include "Message.h"
#include <QGraphicsDropShadowEffect>
#include <QFont>

Message::Message(QGraphicsItem *parent) :
	QGraphicsTextItem{parent}
{
	auto *effect{new QGraphicsDropShadowEffect(this)};

	effect->setColor(0x00FFFFFF);
	effect->setOffset(0, 4);
	// effect->setBlurRadius(20);

	setDefaultTextColor(0xFBC02D);
	setFont(QFont("Neucha", 60, QFont::Bold, false));
	setGraphicsEffect(effect);
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
