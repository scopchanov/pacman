#ifndef ABSTRACTANIMATE_H
#define ABSTRACTANIMATE_H

#include "actions/AbstractTimedAction.h"
#include <QtGlobal>

class AbstractAnimate : public AbstractTimedAction
{
public:
	enum DirectionType : int {
		DIR_Backwards = -1,
		DIR_Forwards = 1
	};

	explicit AbstractAnimate(AbstractComponent *parent = nullptr);

	qreal frameRate() const;
	void setFrameRate(qreal frameRate);
	qreal value() const;
	void setValue(qreal value);
	DirectionType direction() const;
	void setDirection(DirectionType direction);
	int type() const override final;

protected:
	void performTasks() override final;
	void updateParent();

private:
	virtual void update() = 0;

	qreal _frameRate;
	DirectionType _direction;
	qreal _value;
};

#endif // ABSTRACTANIMATE_H
