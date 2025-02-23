#ifndef PLAYERORIENTATING_H
#define PLAYERORIENTATING_H

#include "AbstractOrientatingBehavior.h"
#include <QtGlobal>

class Vector2;

class PlayerOrientating : public AbstractOrientatingBehavior
{
public:
	explicit PlayerOrientating(GameObject *parent = nullptr);

private:
	void performOrientationActions() override;
	qreal directionToAngle(const Vector2 &direction) const;
};

#endif // PLAYERORIENTATING_H
