#include "CharacterMovement.h"
#include "engine/GameObject.h"
#include "engine/GameTimer.h"
#include "engine/Tilemap.h"
#include "engine/Grid.h"
#include <QHash>

CharacterMovement::CharacterMovement(GameObject *parent) :
	AbstractSpatialBehavior(parent),
	m_movingSpeed{0.0},
	m_direction{Vector2(-1, 0)}
{
	if (!parent)
		return;

	m_targetPosition = Vector2(parent->pos());
}

qreal CharacterMovement::movingSpeed() const
{
	return m_movingSpeed;
}

void CharacterMovement::setMovingSpeed(qreal value)
{
	m_movingSpeed = value;
}

Vector2 CharacterMovement::nextMove() const
{
	return m_nextMove;
}

void CharacterMovement::setNextMove(const Vector2 &direction)
{
	m_nextMove = direction;
}

Vector2 CharacterMovement::direction() const
{
	return m_direction;
}

Vector2 CharacterMovement::targetPosition() const
{
	return m_targetPosition;
}

void CharacterMovement::relocateGameObject(const QPointF destination)
{
	const QSizeF &cellSize{tilemap()->grid()->cellSize()};
	const Vector2 &a{m_direction*Vector2(cellSize.width(), cellSize.height())};

	parent()->setPos(destination);
	m_targetPosition = a + destination;
}

void CharacterMovement::reverse()
{
	m_nextMove = m_direction*Vector2(-1, -1);
}

QList<Vector2> CharacterMovement::possibleMoves() const
{
	QList<Vector2> directions;
	const Vector2 &forward{m_direction};
	const Vector2 &left{forward.perpendicular()};
	const Vector2 &right{left.reversed()};

	if (canMove(forward))
		directions.append(forward);

	if (canMove(left))
		directions.append(left);

	if (canMove(right))
		directions.append(right);

	return directions;
}

int CharacterMovement::type() const
{
	return BT_CharacterMovement;
}

void CharacterMovement::performSpatialActions()
{
	moveCharacter();
	decideWhatToDoNext();
}

void CharacterMovement::moveCharacter()
{
	qreal maxDistanceDelta{m_movingSpeed*gameTimer()->deltaTime()};
	Vector2 position{parent()->pos()};

	position.moveTowards(m_targetPosition, maxDistanceDelta);
	parent()->setPos(position.toPointF());
}

void CharacterMovement::decideWhatToDoNext()
{
	if (canMove(m_nextMove))
		turnWhenAligned();
	else if (canMove(m_direction))
		keepMovingInTheSameDirection();
	else
		setCurrentCellAsTarget();
}

void CharacterMovement::turnWhenAligned()
{
	if (aligned())
		makeNextMove();
}

void CharacterMovement::makeNextMove()
{
	m_targetPosition = nextCellPosition(m_nextMove);
	m_direction = m_nextMove;
}

bool CharacterMovement::aligned() const
{
	return distanceToTarget() < 0.001;
}

qreal CharacterMovement::distanceToTarget() const
{
	return Vector2(parent()->pos()).distanceTo(m_targetPosition);
}

void CharacterMovement::keepMovingInTheSameDirection()
{
	m_targetPosition = nextCellPosition(m_direction);
}

void CharacterMovement::setCurrentCellAsTarget()
{
	m_targetPosition = currentCellPosition();
}

Vector2 CharacterMovement::currentCellPosition() const
{
	const Vector2 &cell{currentCell()};
	qreal row{cell.y()};
	qreal column{cell.x()};
	const QPointF &cellPos{tilemap()->grid()->cellPosition(row, column)};

	return Vector2(cellPos);
}

Vector2 CharacterMovement::nextCellPosition(const Vector2 &direction) const
{
	Vector2 srcCell{tilemap()->grid()->posToCell(parent()->pos())};
	const Vector2 &dstCell{srcCell + direction};

	return Vector2(tilemap()->grid()->cellPosition(dstCell.y(), dstCell.x()));
}

bool CharacterMovement::canMove(const Vector2 &direction) const
{
	const QPoint &nextCell{(currentCell() + direction).toPoint()};
	int row{nextCell.y()};
	int column{nextCell.x()};

	return !tilemap()->hasTile(row, column);
}
