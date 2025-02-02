#include "CharacterMovement.h"
#include "engine/GameObject.h"
#include "engine/GameTimer.h"
#include "engine/Tilemap.h"

CharacterMovement::CharacterMovement(GameObject *parent) :
	AbstractCharacterBehavior(parent),
	m_movingSpeed{0.0}
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

void CharacterMovement::performCharacterActions()
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
	if (distanceToTarget() >= 0.5)
		return;

	if (canMove(m_nextMove))
		turnWhenAligned();
	else if (canMove(m_direction))
		keepMovingInTheSameDirection();
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
	return distanceToTarget() < 0.01;
}

qreal CharacterMovement::distanceToTarget() const
{
	return Vector2(parent()->pos()).distanceTo(m_targetPosition);
}

void CharacterMovement::keepMovingInTheSameDirection()
{
	m_targetPosition = nextCellPosition(m_direction);
}

bool CharacterMovement::canMove(const Vector2 &direction) const
{
	const QPoint &nextCell{(currentCell() + direction).toPoint()};
	int row{nextCell.y()};
	int column{nextCell.x()};

	return !tilemap()->hasTile(row, column);
}

Vector2 CharacterMovement::nextCellPosition(const Vector2 &direction) const
{
	Vector2 srcCell{tilemap()->posToCell(parent()->pos())};
	const Vector2 &dstCell{srcCell + direction};

	return Vector2(tilemap()->cellPosition(dstCell.x(), dstCell.y()));
}
