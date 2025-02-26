#ifndef ABSTRACTORIENTATINGBEHAVIOR_H
#define ABSTRACTORIENTATINGBEHAVIOR_H

#include "AbstractBehavior.h"

class Moving;

class AbstractOrientatingBehavior : public AbstractBehavior
{
public:
	explicit AbstractOrientatingBehavior(AbstractComponent *parent = nullptr);

	Moving *moving() const;
	void setMoving(Moving *moving);
	int type() const override final;

	void reset() override;

protected:
	void performTasks() override final;

private:
	virtual void performOrientationActions() = 0;

	Moving *_moving;
};

#endif // ABSTRACTORIENTATINGBEHAVIOR_H
