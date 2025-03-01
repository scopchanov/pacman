#ifndef ACTIVATEDEENERGIZER_H
#define ACTIVATEDEENERGIZER_H

#include <AbstractAction.h>

class ActivateDeenergizer : public AbstractAction
{
public:
	explicit ActivateDeenergizer(AbstractComponent *parent = nullptr);

	int type() const override;

protected:
	void performTasks() override;
};

#endif // ACTIVATEDEENERGIZER_H
