#ifndef ABSTRACTCONTROLLINGBEHAVIOR_H
#define ABSTRACTCONTROLLINGBEHAVIOR_H

#include <AbstractBehavior.h>

class Moving;

class AbstractControllingBehavior : public AbstractBehavior
{
public:
	explicit AbstractControllingBehavior(AbstractComponent *parent = nullptr);

	Moving *moving() const;
	void setMoving(Moving *moving);
	int type() const override final;

protected:
	void performTasks() override;

private:
	virtual void performControllingActions() = 0;

	Moving *_moving;
};

#endif // ABSTRACTCONTROLLINGBEHAVIOR_H
