#ifndef ABSTRACTCONTROL_H
#define ABSTRACTCONTROL_H

#include <AbstractAction.h>

class Moving;

class AbstractControl : public AbstractAction
{
public:
	explicit AbstractControl(AbstractComponent *parent = nullptr);

	Moving *moving() const;
	void setMoving(Moving *moving);
	int type() const override final;

protected:
	void performTasks() override;
	virtual void performControlTasks() = 0;

private:
	Moving *_moving;
};

#endif // ABSTRACTCONTROL_H
