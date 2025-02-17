#ifndef CALMDOWNENEMIES_H
#define CALMDOWNENEMIES_H

#include "AbstractAction.h"

class CalmDownEnemies : public AbstractAction
{
public:
	explicit CalmDownEnemies(AbstractBehavior *parent = nullptr);

	int type() const override;

private:
	void performTask() override;
};

#endif // CALMDOWNENEMIES_H
