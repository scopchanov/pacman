#ifndef MOVING_H
#define MOVING_H

#include "AbstractSpatialBehavior.h"
#include <QtGlobal>
#include <QPointF>

class Moving : public AbstractSpatialBehavior
{
public:
	explicit Moving(AbstractComponent *parent = nullptr);

	qreal speed() const;
	void setSpeed(qreal speed);
	Vector2 initialDirection() const;
	void setInitialDirection(const Vector2 &direction);
	Vector2 currentDirection() const;
	Vector2 nextDirection() const;
	void setNextDirection(const Vector2 &direction);
	Vector2 nextCellPositionIn(const Vector2 &direction) const;
	QList<Vector2> possibleMoves() const;
	int type() const override;

	void relocateCharacter(const QPointF &destination);
	void reverse();
	void reset() override;

protected:
	void performSpatialActions() override;

private:
	void moveCharacter();
	void chooseHeading();
	bool headIn(const Vector2 &direction);
	void changeDirection(const Vector2 &direction);
	void targetParentPosition();
	void targetCurrentCell();
	void targetNextCell();
	bool alignedWithTargetCellCenter() const;
	bool canMoveIn(const Vector2 &direction) const;
	bool isUnderDoor() const;
	bool isWayClear(const Vector2 &direction) const;
	Vector2 cellPosition(const Vector2 &cell) const;
	Vector2 parentPosition() const;
	void setParentPosition(const QPointF &position);

	qreal _speed;
	Vector2 _initialDirection;
	Vector2 _currentDirection;
	Vector2 _nextDirection;
	Vector2 _targetPosition;
};

#endif // MOVING_H
