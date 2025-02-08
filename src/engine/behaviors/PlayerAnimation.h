#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include "AbstractTimedBehavior.h"
#include <QtGlobal>

class PlayerAnimation : public AbstractTimedBehavior
{
public:
	explicit PlayerAnimation(GameObject *parent = nullptr);

	int type() const override;

	void reset() override;

private:
	void performTimedActions() override;

	qreal m_angle;
};

#endif // PLAYERANIMATION_H
