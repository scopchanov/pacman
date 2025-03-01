#include "Move.h"
#include "AbstractGameObject.h"
#include "Clock.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "Grid.h"
#include "Tilemap.h"

Move::Move(AbstractComponent *parent) :
	AbstractTilemapAction(parent),
	_speed{0.0},
	_initialDirection{V2_LEFT},
	_currentDirection{_initialDirection}
{

}

qreal Move::speed() const
{
	return _speed;
}

void Move::setSpeed(qreal speed)
{
	_speed = speed;
}

Vector2 Move::initialDirection() const
{
	return _initialDirection;
}

void Move::setInitialDirection(const Vector2 &direction)
{
	_initialDirection = direction;
	_currentDirection = _initialDirection;
}

Vector2 Move::currentDirection() const
{
	return _currentDirection;
}

Vector2 Move::nextDirection() const
{
	return _nextDirection;
}

void Move::setNextDirection(const Vector2 &direction)
{
	_nextDirection = direction;
}

Vector2 Move::nextCellPositionIn(const Vector2 &direction) const
{
	return cellPosition(currentCell() + direction);
}

QList<Vector2> Move::possibleMoves() const
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

int Move::type() const
{
	return ACT_Move;
}

void Move::relocateCharacter(const QPointF &destination)
{
	setParentPosition(destination);
	targetNextCell();
}

void Move::reverse()
{
	// changeDirection(_currentDirection.reversed());
}

void Move::reset()
{
	_currentDirection = _initialDirection;
	_nextDirection = _currentDirection;

	targetParentPosition();
}

void Move::performTasks()
{
	chooseHeading();
	moveCharacter();
}

Tilemap *Move::tilemap() const
{
	return Game::ref().level()->walls();
}

void Move::moveCharacter()
{
	qreal step{_speed*Game::ref().clock()->deltaTime()};

	setParentPosition(parentPosition().movedTowards(_targetPosition, step));
}

void Move::chooseHeading()
{
	if (!headIn(_nextDirection) && !headIn(_currentDirection))
		targetCurrentCell();
}

bool Move::headIn(const Vector2 &direction)
{
	if (!canMoveIn(direction))
		return false;

	if (alignedWithTargetCellCenter())
		changeDirection(direction);

	return true;
}

void Move::changeDirection(const Vector2 &direction)
{
	_currentDirection = direction;

	targetNextCell();
}

void Move::targetParentPosition()
{
	if (!gameObject())
		return;

	_targetPosition = parentPosition();
}

void Move::targetCurrentCell()
{
	_targetPosition = cellPosition(currentCell());
}

void Move::targetNextCell()
{
	_targetPosition = nextCellPositionIn(_currentDirection);
}

bool Move::alignedWithTargetCellCenter() const
{
	return parentPosition().distanceTo(_targetPosition) < 0.001;
}

bool Move::canMoveIn(const Vector2 &direction) const
{
	return isUnderDoor() ? true : isWayClear(direction);
}

bool Move::isUnderDoor() const
{
	return currentCell() == QPoint(14, 14) || currentCell() == QPoint(14, 15);
}

bool Move::isWayClear(const Vector2 &direction) const
{
	return !tilemap()->hasTile(currentCell() + direction);
}

Vector2 Move::cellPosition(const Vector2 &cell) const
{
	return tilemap()->grid()->mapFromGrid(cell);
}

Vector2 Move::parentPosition() const
{
	return Vector2(gameObject()->pos());
}

void Move::setParentPosition(const QPointF &position)
{
	gameObject()->setPos(position);
}
