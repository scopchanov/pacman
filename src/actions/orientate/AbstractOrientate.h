#ifndef ABSTRACTORIENTATE_H
#define ABSTRACTORIENTATE_H

#include "AbstractAction.h"

class Moving;

class AbstractOrientate : public AbstractAction
{
public:
	explicit AbstractOrientate(AbstractComponent *parent = nullptr);

	Moving *moving() const;
	void setMoving(Moving *moving);
	int type() const override final;

protected:
	void performTasks() override final;
	virtual void orientate() = 0;

private:
	Moving *_moving;
};

#endif // ABSTRACTORIENTATE_H
