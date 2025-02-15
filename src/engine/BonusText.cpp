#include "BonusText.h"
#include <QFont>

BonusText::BonusText(GameObject *parent) :
	GameObject(parent),
	_textItem{new QGraphicsTextItem(this)}
{
	_textItem->setDefaultTextColor(0xFFFFFF);
	_textItem->setFont(QFont("Neucha", 16, QFont::Bold, false));
}

void BonusText::setText(const QString &text)
{
	const QRectF &rect{_textItem->boundingRect()};

	_textItem->setPlainText(text);
	_textItem->setPos(-rect.width()/2.0, -rect.height()/2.0);
}
