#ifndef DEENERGIZEPLAYER_H
#define DEENERGIZEPLAYER_H

#include "AbstractAction.h"

class DeenergizePlayer : public AbstractAction
{
public:
	explicit DeenergizePlayer(AbstractBehavior *parent = nullptr);

	int type() const override;

private:
	void performTask() override;
};

#endif // DEENERGIZEPLAYER_H
