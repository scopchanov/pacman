#ifndef PLAYERORIENTATION_H
#define PLAYERORIENTATION_H

#include "AbstractOrientationBehavior.h"
#include <QtGlobal>

class Vector2;

class PlayerOrientation : public AbstractOrientationBehavior
{
public:
	explicit PlayerOrientation(GameObject *parent = nullptr);

private:
	void performOrientationActions() override;
	qreal directionToAngle(const Vector2 &direction) const;
};

#endif // PLAYERORIENTATION_H
