#ifndef ABSTRACTANIMATINGBEHAVIOR_H
#define ABSTRACTANIMATINGBEHAVIOR_H

#include "AbstractTimedBehavior.h"
#include <QtGlobal>

class AbstractAnimatingBehavior : public AbstractTimedBehavior
{
public:
	enum DirectionType : int {
		DIR_Backwards = -1,
		DIR_Forwards = 1
	};

	explicit AbstractAnimatingBehavior(AbstractGameObject *parent = nullptr);

	qreal frameRate() const;
	void setFrameRate(qreal frameRate);
	qreal value() const;
	void setValue(qreal value);
	DirectionType direction() const;
	void setDirection(DirectionType direction);
	int type() const override;

	void reset() override;

protected:
	void updateParent();

private:
	void performActions() override final;
	virtual void update() = 0;

	qreal _frameRate;
	DirectionType _direction;
	qreal _value;
};

#endif // ABSTRACTANIMATINGBEHAVIOR_H
