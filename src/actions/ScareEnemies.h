#ifndef SCAREENEMIES_H
#define SCAREENEMIES_H

#include "AbstractAction.h"

class ScareEnemies : public AbstractAction
{
public:
	explicit ScareEnemies(AbstractComponent *parent = nullptr);

	int type() const override;

private:
	void performTasks() override;
};

#endif // SCAREENEMIES_H
