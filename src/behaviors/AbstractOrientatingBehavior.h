#ifndef ABSTRACTORIENTATINGBEHAVIOR_H
#define ABSTRACTORIENTATINGBEHAVIOR_H

#include "AbstractBehavior.h"

class Moving;

class AbstractOrientatingBehavior : public AbstractBehavior
{
public:
	explicit AbstractOrientatingBehavior(AbstractGameObject *parent = nullptr);

	Moving *moving() const;
	void setMoving(Moving *moving);
	int type() const override;

	void reset() override;

private:
	void performActions() override final;
	virtual void performOrientationActions() = 0;

	Moving *_moving;
};

#endif // ABSTRACTORIENTATINGBEHAVIOR_H
