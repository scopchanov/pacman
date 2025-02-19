#include "BonusText.h"
#include "GameGlobals.h"
#include <QFont>

BonusText::BonusText(GameObject *parent) :
	GameObject(parent),
	_textItem{new QGraphicsTextItem(this)}
{
	_textItem->setDefaultTextColor(0xFFFFFF);
	_textItem->setFont(QFont("Neucha", 16, QFont::Black, false));
}

void BonusText::setText(const QString &text)
{
	_textItem->setPlainText(text);

	reposition();
}

int BonusText::objectType() const
{
	return OBJ_Npc;
}

void BonusText::reposition()
{
	const QRectF &rect{_textItem->boundingRect()};

	_textItem->setPos(-rect.width()/2.0, -rect.height()/2.0);
}
