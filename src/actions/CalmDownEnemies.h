#ifndef CALMDOWNENEMIES_H
#define CALMDOWNENEMIES_H

#include "AbstractAction.h"

class CalmDownEnemies : public AbstractAction
{
public:
	explicit CalmDownEnemies(AbstractComponent *parent = nullptr);

	int type() const override;

protected:
	void performTasks() override;
};

#endif // CALMDOWNENEMIES_H
