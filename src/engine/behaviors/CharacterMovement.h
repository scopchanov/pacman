#ifndef CHARACTERMOVEMENT_H
#define CHARACTERMOVEMENT_H

#include "AbstractSpatialBehavior.h"
#include <QtGlobal>
#include <QPointF>

class CharacterMovement : public AbstractSpatialBehavior
{
public:
	enum DirectionIndex : int {
		DIR_Left = 0,
		DIR_Right,
		DIR_Up,
		DIR_Down
	};

	explicit CharacterMovement(GameObject *parent = nullptr);

	qreal movingSpeed() const;
	void setMovingSpeed(qreal value);
	Vector2 nextMove() const;
	void setNextMove(const Vector2 &direction);
	Vector2 direction() const;
	Vector2 targetPosition() const;
	Vector2 nextCellPosition(const Vector2 &direction) const;
	void relocateGameObject(const QPointF destination);
	void reverse();
	QList<Vector2> possibleMoves() const;
	int type() const override;

private:
	void performSpatialActions() override;
	void moveCharacter();
	void decideWhatToDoNext();
	void turnWhenAligned();
	void makeNextMove();
	bool aligned() const;
	qreal distanceToTarget() const;
	void keepMovingInTheSameDirection();
	void setCurrentCellAsTarget();
	Vector2 currentCellPosition() const;
	bool canMove(const Vector2 &direction) const;

	qreal m_movingSpeed;
	Vector2 m_nextMove;
	Vector2 m_direction;
	Vector2 m_targetPosition;
};

#endif // CHARACTERMOVEMENT_H
