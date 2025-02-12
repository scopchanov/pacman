#ifndef ABSTRACTANIMATIONBEHAVIOR_H
#define ABSTRACTANIMATIONBEHAVIOR_H

#include "AbstractTimedBehavior.h"
#include <QtGlobal>

class AbstractAnimationBehavior : public AbstractTimedBehavior
{
public:
	enum DirectionType : int {
		DIR_Backwards = -1,
		DIR_Forwards = 1
	};

	explicit AbstractAnimationBehavior(GameObject *parent = nullptr);

	qreal frameRate() const;
	void setFrameRate(qreal frameRate);
	qreal value() const;
	void setValue(qreal value);
	DirectionType direction() const;
	void setDirection(DirectionType direction);
	int gameObjectType() const;
	void setGameObjectType(int type);
	int type() const override;

	void reset() override;

protected:
	void updateParent();

private:
	void performTimedActions() override final;
	virtual void update() = 0;

	int _gameObjectType;
	qreal _frameRate;
	DirectionType _direction;
	qreal _value;
};

#endif // ABSTRACTANIMATIONBEHAVIOR_H
