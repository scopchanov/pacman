#include "CharacterMovement.h"
#include "engine/GameObject.h"
#include "engine/GameClock.h"
#include "engine/Grid.h"
#include "engine/Tilemap.h"

CharacterMovement::CharacterMovement(GameObject *parent) :
	AbstractSpatialBehavior(parent),
	_movingSpeed{0.0},
	_initialDirection{Vector2(-1, 0)},
	_currentDirection{_initialDirection}
{
	targetParentPosition();
}

qreal CharacterMovement::movingSpeed() const
{
	return _movingSpeed;
}

void CharacterMovement::setMovingSpeed(qreal speed)
{
	_movingSpeed = speed;
}

Vector2 CharacterMovement::initialDirection() const
{
	return _initialDirection;
}

void CharacterMovement::setInitialDirection(const Vector2 &direction)
{
	_initialDirection = direction;
	_currentDirection = _initialDirection;
}

Vector2 CharacterMovement::currentDirection() const
{
	return _currentDirection;
}

Vector2 CharacterMovement::nextDirection() const
{
	return _nextDirection;
}

void CharacterMovement::setNextDirection(const Vector2 &direction)
{
	_nextDirection = direction;
}

Vector2 CharacterMovement::nextCellPositionIn(const Vector2 &direction) const
{
	return cellPosition(currentCell() + direction);
}

QList<Vector2> CharacterMovement::possibleMoves() const
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

int CharacterMovement::type() const
{
	return BT_CharacterMovement;
}

void CharacterMovement::relocateCharacter(const QPointF &destination)
{
	setParentPosition(destination);
	targetNextCell();
}

void CharacterMovement::reverse()
{
	// changeDirection(_currentDirection.reversed());
}

void CharacterMovement::reset()
{
	_currentDirection = _initialDirection;
	_nextDirection = V2_ZERO;

	targetParentPosition();
}

void CharacterMovement::performSpatialActions()
{
	chooseHeading();
	moveCharacter();
}

void CharacterMovement::moveCharacter()
{
	qreal step{_movingSpeed*gameClock()->deltaTime()};

	setParentPosition(parentPosition().movedTowards(_targetPosition, step));
}

void CharacterMovement::chooseHeading()
{
	if (!headIn(_nextDirection) && !headIn(_currentDirection))
		targetCurrentCell();
}

bool CharacterMovement::headIn(const Vector2 &direction)
{
	if (!canMoveIn(direction))
		return false;

	if (alignedWithTargetCellCenter())
		changeDirection(direction);

	return true;
}

void CharacterMovement::changeDirection(const Vector2 &direction)
{
	_currentDirection = direction;

	targetNextCell();
}

void CharacterMovement::targetParentPosition()
{
	if (!parent())
		return;

	_targetPosition = parentPosition();
}

void CharacterMovement::targetCurrentCell()
{
	_targetPosition = cellPosition(currentCell());
}

void CharacterMovement::targetNextCell()
{
	_targetPosition = nextCellPositionIn(_currentDirection);
}

bool CharacterMovement::alignedWithTargetCellCenter() const
{
	return parentPosition().distanceTo(_targetPosition) < 0.001;
}

bool CharacterMovement::canMoveIn(const Vector2 &direction) const
{
	return isUnderDoor() ? true : isWayClear(direction);
}

bool CharacterMovement::isUnderDoor() const
{
	return currentCell() == QPoint(14, 14) || currentCell() == QPoint(14, 15);
}

bool CharacterMovement::isWayClear(const Vector2 &direction) const
{
	return !tilemap()->hasTile(currentCell() + direction);
}

Vector2 CharacterMovement::cellPosition(const Vector2 &cell) const
{
	return tilemap()->grid()->cellPosition(cell);
}

Vector2 CharacterMovement::parentPosition() const
{
	return Vector2(parent()->pos());
}

void CharacterMovement::setParentPosition(const QPointF &position)
{
	parent()->setPos(position);
}
