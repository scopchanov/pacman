#include "EnemyController.h"
#include "engine/AiStateMachine.h"
#include "engine/Enemy.h"
#include "engine/Grid.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/personalities/AbstractPersonality.h"
#include <QGraphicsScene>
#include <QRandomGenerator>

EnemyController::EnemyController(Enemy *parent) :
	AbstractBehavior(parent),
	_globalState{GS_Scatter},
	_grid{nullptr},
	_characterMovement{nullptr},
	_targetMark{new QGraphicsRectItem(-10, -10, 20, 20)}
{
	_targetMark->setPen(QPen(Qt::transparent));
}

void EnemyController::setGlobalState(GlobalState state)
{
	_globalState = state;
}

void EnemyController::setCharacterMovement(CharacterMovement *characterMovement)
{
	_characterMovement = characterMovement;
}

Grid *EnemyController::grid() const
{
	return _grid;
}

void EnemyController::setGrid(Grid *grid)
{
	_grid = grid;
}

int EnemyController::type() const
{
	return BT_EnemyController;
}

void EnemyController::reset()
{
	parentEnemy()->setState(Enemy::ST_Exit);
	_targetPosition = QPointF(360, 300);
}

void EnemyController::performActions()
{
	if (!_characterMovement || !_grid)
		return;

	updateTargetPosition();

	const QList<Vector2> &directions{_characterMovement->possibleMoves()};

	if (directions.isEmpty()) {
		_characterMovement->reverse();
		return;
	}

	qreal minimalDistence{distanceToTarget(directions.first())};
	int index{0};
	int n{1};

	const QList<Vector2> &lastDirections{directions.last(directions.count() - 1)};

	for (const auto &direction : lastDirections) {
		qreal distance{distanceToTarget(direction)};

		if (distance < minimalDistence) {
			minimalDistence = distance;
			index = n;
		}

		n++;
	}

	_characterMovement->setNextDirection(directions.at(index));

#ifdef DEBUG
	if (!_targetMark->scene())
		parent()->scene()->addItem(_targetMark);

	_targetMark->setPos(_targetPosition);
	_targetMark->setBrush(parent()->brush());
	_targetMark->update();
#endif
}

qreal EnemyController::distanceToTarget(Vector2 direction) const
{
	// TODO: Improve me

	return _characterMovement->nextCellPositionIn(direction).distanceTo(Vector2(_targetPosition));
}

void EnemyController::updateTargetPosition()
{
	switch (parentEnemy()->state()) {
	case Enemy::ST_Exit:
	case Enemy::ST_Eaten:
		_targetPosition = QPointF(360, 300);

		if (isTargetReached())
			parentEnemy()->calmDown();
		break;
	case Enemy::ST_Frightened:
		actFrightened();
		break;
	case Enemy::ST_Global:
		processGlobalState();
		break;
	default:
		break;
	}
}

bool EnemyController::isTargetReached()
{
	const QPoint &parentCell{_grid->mapToGrid(parent()->pos())};
	const QPoint &targetCell{_grid->mapToGrid(_targetPosition)};

	return parentCell == targetCell;
}

void EnemyController::processGlobalState()
{
	auto *personality{parentEnemy()->personality()};

	switch (_globalState) {
	case GS_Scatter:
		_targetPosition = personality->scatterTarget();
		break;
	case GS_Chase:
		_targetPosition = personality->calculateTarget();
		break;
	}
}

void EnemyController::actFrightened()
{
	// ranadom movement
	// int cnt{static_cast<int>(directions.count())};
	// int ind{QRandomGenerator::global()->bounded(0, cnt)};
	// _characterMovement->setNextMove(directions.at(ind));
}

Enemy *EnemyController::parentEnemy()
{
	return static_cast<Enemy *>(parent());
}
