#ifndef SCAREENEMIES_H
#define SCAREENEMIES_H

#include "AbstractAction.h"

class ScareEnemies : public AbstractAction
{
public:
	explicit ScareEnemies(AbstractBehavior *parent = nullptr);

	int type() const override;

private:
	void performTask() override;
};

#endif // SCAREENEMIES_H
