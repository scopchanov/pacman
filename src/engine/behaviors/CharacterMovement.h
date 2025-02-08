#ifndef CHARACTERMOVEMENT_H
#define CHARACTERMOVEMENT_H

#include "AbstractSpatialBehavior.h"
#include <QtGlobal>
#include <QPointF>

class CharacterMovement : public AbstractSpatialBehavior
{
public:
	explicit CharacterMovement(GameObject *parent = nullptr);

	qreal movingSpeed() const;
	void setMovingSpeed(qreal value);
	Vector2 currentDirection() const;
	Vector2 nextDirection() const;
	void setNextDirection(const Vector2 &direction);
	Vector2 nextCellPositionIn(const Vector2 &direction) const;
	QList<Vector2> possibleMoves() const;
	int type() const override;

	void relocateCharacter(const QPointF &destination);
	void reverse();
	void reset() override;

private:
	void performSpatialActions() override;
	void moveCharacter();
	void chooseHeading();
	bool headIn(const Vector2 &direction);
	void changeDirection(const Vector2 &direction);
	void targetParentPosition();
	void targetCurrentCell();
	void targetNextCell();
	bool alignedWithTargetCellCenter() const;
	qreal distanceToTargetCell() const;
	bool canMoveIn(const Vector2 &direction) const;
	bool isUnderDoor() const;
	bool isWayClear(const Vector2 &direction) const;
	Vector2 currentCellPosition() const;

	qreal _movingSpeed;
	Vector2 _currentDirection;
	Vector2 _nextDirection;
	Vector2 _targetCellPosition;
};

#endif // CHARACTERMOVEMENT_H
