#include "Moving.h"
#include "Clock.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "Grid.h"
#include "Tilemap.h"

Moving::Moving(AbstractGameObject *parent) :
	AbstractSpatialBehavior(parent),
	_speed{0.0},
	_initialDirection{V2_LEFT},
	_currentDirection{_initialDirection}
{

}

qreal Moving::speed() const
{
	return _speed;
}

void Moving::setSpeed(qreal speed)
{
	_speed = speed;
}

Vector2 Moving::initialDirection() const
{
	return _initialDirection;
}

void Moving::setInitialDirection(const Vector2 &direction)
{
	_initialDirection = direction;
	_currentDirection = _initialDirection;
}

Vector2 Moving::currentDirection() const
{
	return _currentDirection;
}

Vector2 Moving::nextDirection() const
{
	return _nextDirection;
}

void Moving::setNextDirection(const Vector2 &direction)
{
	_nextDirection = direction;
}

Vector2 Moving::nextCellPositionIn(const Vector2 &direction) const
{
	return cellPosition(currentCell() + direction);
}

QList<Vector2> Moving::possibleMoves() const
{
	QList<Vector2> directions;
	const Vector2 &forwardDirection{_currentDirection};
	const Vector2 &leftDirection{forwardDirection.perpendicular()};
	const Vector2 &rightDirection{leftDirection.reversed()};

	if (canMoveIn(forwardDirection))
		directions.append(forwardDirection);

	if (canMoveIn(leftDirection))
		directions.append(leftDirection);

	if (canMoveIn(rightDirection))
		directions.append(rightDirection);

	return directions;
}

int Moving::type() const
{
	return BT_Moving;
}

void Moving::relocateCharacter(const QPointF &destination)
{
	setParentPosition(destination);
	targetNextCell();
}

void Moving::reverse()
{
	// changeDirection(_currentDirection.reversed());
}

void Moving::reset()
{
	_currentDirection = _initialDirection;
	_nextDirection = _currentDirection;

	targetParentPosition();
}

void Moving::performSpatialActions()
{
	chooseHeading();
	moveCharacter();
}

void Moving::moveCharacter()
{
	qreal step{_speed*clock()->deltaTime()};

	setParentPosition(parentPosition().movedTowards(_targetPosition, step));
}

void Moving::chooseHeading()
{
	if (!headIn(_nextDirection) && !headIn(_currentDirection))
		targetCurrentCell();
}

bool Moving::headIn(const Vector2 &direction)
{
	if (!canMoveIn(direction))
		return false;

	if (alignedWithTargetCellCenter())
		changeDirection(direction);

	return true;
}

void Moving::changeDirection(const Vector2 &direction)
{
	_currentDirection = direction;

	targetNextCell();
}

void Moving::targetParentPosition()
{
	if (!parent())
		return;

	_targetPosition = parentPosition();
}

void Moving::targetCurrentCell()
{
	_targetPosition = cellPosition(currentCell());
}

void Moving::targetNextCell()
{
	_targetPosition = nextCellPositionIn(_currentDirection);
}

bool Moving::alignedWithTargetCellCenter() const
{
	return parentPosition().distanceTo(_targetPosition) < 0.001;
}

bool Moving::canMoveIn(const Vector2 &direction) const
{
	return isUnderDoor() ? true : isWayClear(direction);
}

bool Moving::isUnderDoor() const
{
	return currentCell() == QPoint(14, 14) || currentCell() == QPoint(14, 15);
}

bool Moving::isWayClear(const Vector2 &direction) const
{
	return !tilemap()->hasTile(currentCell() + direction);
}

Vector2 Moving::cellPosition(const Vector2 &cell) const
{
	return tilemap()->grid()->mapFromGrid(cell);
}

Vector2 Moving::parentPosition() const
{
	return Vector2(parent()->pos());
}

void Moving::setParentPosition(const QPointF &position)
{
	parent()->setPos(position);
}
