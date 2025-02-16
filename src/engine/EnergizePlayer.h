#ifndef ENERGIZEPLAYER_H
#define ENERGIZEPLAYER_H

#include "AbstractAction.h"

class EnergizePlayer : public AbstractAction
{
public:
	explicit EnergizePlayer(AbstractBehavior *parent = nullptr);

	int type() const override;

private:
	void performTask() override;
};

#endif // ENERGIZEPLAYER_H
