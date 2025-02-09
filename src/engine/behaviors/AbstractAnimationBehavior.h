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

	qreal frameTime() const;
	void setFrameTime(qreal frameTime);
	qreal value() const;
	void setValue(qreal value);
	DirectionType direction() const;
	void setDirection(DirectionType direction);
	int type() const override;

private:
	void performTimedActions() override final;
	virtual void foo() = 0;
	virtual void updateParent() = 0;

	qreal _frameTime;
	qreal _value;
	DirectionType _direction;
};

#endif // ABSTRACTANIMATIONBEHAVIOR_H
