#ifndef DEACTIVATEDEENERGIZER_H
#define DEACTIVATEDEENERGIZER_H

#include <AbstractAction.h>

class DeactivateDeenergizer : public AbstractAction
{
public:
	explicit DeactivateDeenergizer(AbstractComponent *parent = nullptr);

	int type() const override;

protected:
	void performTasks() override;
};

#endif // DEACTIVATEDEENERGIZER_H
