#ifndef PLAYERORIENTATION_H
#define PLAYERORIENTATION_H

#include "AbstractBehavior.h"
#include <QtGlobal>

class CharacterMovement;
class Vector2;

class PlayerOrientation : public AbstractBehavior
{
public:
	explicit PlayerOrientation(GameObject *parent = nullptr);

	void setMovement(CharacterMovement *movement);
	int type() const override;

private:
	void performActions() override;
	qreal directionToAngle(const Vector2 &direction) const;

	CharacterMovement *m_movement;
};

#endif // PLAYERORIENTATION_H
