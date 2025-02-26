#ifndef ENABLEDEENERGIZER_H
#define ENABLEDEENERGIZER_H

#include <AbstractAction.h>

class EnableDeenergizer : public AbstractAction
{
public:
	explicit EnableDeenergizer(AbstractComponent *parent = nullptr);

	int type() const override;

private:
	void performTasks() override;
};

#endif // ENABLEDEENERGIZER_H
