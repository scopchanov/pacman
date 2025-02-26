#ifndef DEENERGIZEPLAYER_H
#define DEENERGIZEPLAYER_H

#include "AbstractAction.h"

class DeenergizePlayer : public AbstractAction
{
public:
	explicit DeenergizePlayer(AbstractComponent *parent = nullptr);

	int type() const override;

protected:
	void performTasks() override;
};

#endif // DEENERGIZEPLAYER_H
