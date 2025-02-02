#ifndef CHARACTERMOVEMENT_H
#define CHARACTERMOVEMENT_H

#include "AbstractCharacterBehavior.h"
#include <QtGlobal>
#include <QPointF>

class CharacterMovement : public AbstractCharacterBehavior
{
public:
	explicit CharacterMovement(GameObject *parent = nullptr);

	qreal movingSpeed() const;
	void setMovingSpeed(qreal value);
	Vector2 nextMove() const;
	void setNextMove(const Vector2 &direction);

protected:
	void performActions() override;

private:
	void moveCharacter();
	void decideWhatToDoNext();
	void turnWhenAligned();
	void makeNextMove();
	bool aligned() const;
	qreal distanceToTarget() const;
	void keepMovingInTheSameDirection();
	bool canMove(const Vector2 &direction) const;
	Vector2 nextCellPosition(const Vector2 &direction) const;

	qreal m_movingSpeed;
	Vector2 m_nextMove;
	Vector2 m_direction;
	Vector2 m_targetPosition;
};

#endif // CHARACTERMOVEMENT_H
