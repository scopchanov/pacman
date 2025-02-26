#ifndef ENERGIZEPLAYER_H
#define ENERGIZEPLAYER_H

#include "AbstractAction.h"

class EnergizePlayer : public AbstractAction
{
public:
	explicit EnergizePlayer(AbstractComponent *parent = nullptr);

	int type() const override;

private:
	void performTasks() override;
};

#endif // ENERGIZEPLAYER_H
