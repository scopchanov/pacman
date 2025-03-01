#ifndef ABSTRACTCHARACTER_H
#define ABSTRACTCHARACTER_H

#include "AbstractGameObject.h"

class AbstractCharacter : public AbstractGameObject
{
public:
	explicit AbstractCharacter(AbstractGameObject *parent = nullptr);

	void setSpeed(qreal percent);

	void reset() override;

protected:
	QColor paletteColor(int role) const;
	virtual int colorRole() const = 0;
};

#endif // ABSTRACTCHARACTER_H
