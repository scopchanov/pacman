#ifndef BONUSTEXT_H
#define BONUSTEXT_H

#include "GameObject.h"

class BonusText : public GameObject
{
public:
	explicit BonusText(GameObject *parent = nullptr);

	void setText(const QString &text);

private:
	QGraphicsTextItem *_textItem;
};

#endif // BONUSTEXT_H
