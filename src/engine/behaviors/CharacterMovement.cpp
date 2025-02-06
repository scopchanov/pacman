#include "CharacterMovement.h"
#include "engine/GameObject.h"
#include "engine/GameTimer.h"
#include "engine/Grid.h"
#include "engine/Tilemap.h"

CharacterMovement::CharacterMovement(GameObject *parent) :
	AbstractSpatialBehavior(parent),
	_movingSpeed{0.0},
	_currentDirection{Vector2(-1, 0)}
{
	targetParentPosition(parent);
}

void CharacterMovement::setParent(GameObject *parent)
{
	targetParentPosition(parent);
}

qreal CharacterMovement::movingSpeed() const
{
	return _movingSpeed;
}

void CharacterMovement::setMovingSpeed(qreal value)
{
	_movingSpeed = value;
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
	const Vector2 &sourceCell{tilemap()->grid()->posToCell(parent()->pos())};

	return tilemap()->grid()->cellPosition(sourceCell + direction);
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
	parent()->setPos(destination);
	targetNextCell();
}

void CharacterMovement::reverse()
{
	_nextDirection = _currentDirection.reversed();
}

void CharacterMovement::performSpatialActions()
{
	chooseHeading();
	moveCharacter();
}

void CharacterMovement::moveCharacter()
{
	qreal rate{_movingSpeed*gameTimer()->deltaTime()};
	const Vector2 &characterPosition{parent()->pos()};

	parent()->setPos(characterPosition.movedTowards(_targetCellPosition, rate));
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

void CharacterMovement::targetParentPosition(GameObject *parent)
{
	if (!parent)
		return;

	_targetCellPosition = parent->pos();
}

void CharacterMovement::targetCurrentCell()
{
	_targetCellPosition = currentCellPosition();
}

void CharacterMovement::targetNextCell()
{
	_targetCellPosition = nextCellPositionIn(_currentDirection);
}

bool CharacterMovement::alignedWithTargetCellCenter() const
{
	return distanceToTargetCell() < 0.001;
}

qreal CharacterMovement::distanceToTargetCell() const
{
	return Vector2(parent()->pos()).distanceTo(_targetCellPosition);
}

bool CharacterMovement::canMoveIn(const Vector2 &direction) const
{
	return !tilemap()->hasTile(currentCell() + direction);
}

Vector2 CharacterMovement::currentCellPosition() const
{
	return tilemap()->grid()->cellPosition(currentCell());
}
