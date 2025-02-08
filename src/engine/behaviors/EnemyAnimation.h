#ifndef ENEMYANIMATION_H
#define ENEMYANIMATION_H

#include "AbstractTimedBehavior.h"
#include <QtGlobal>

class EnemyAnimation : public AbstractTimedBehavior
{
public:
	explicit EnemyAnimation(GameObject *parent = nullptr);

	int type() const override;

	void reset() override;

private:
	void performTimedActions() override;

	qreal _value;
	int _n;
};

#endif // ENEMYANIMATION_H
