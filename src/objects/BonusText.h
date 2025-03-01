#ifndef BONUSTEXT_H
#define BONUSTEXT_H

#include "AbstractGameObject.h"

class BonusText : public AbstractGameObject
{
public:
	explicit BonusText(AbstractGameObject *parent = nullptr);

	void setText(const QString &text);
	int objectType() const override final;

private:
	void reposition();

	QGraphicsTextItem *_textItem;
};

#endif // BONUSTEXT_H
