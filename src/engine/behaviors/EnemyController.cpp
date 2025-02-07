#include "EnemyController.h"
#include "engine/Vector2.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/GameObject.h"
#include "engine/Tilemap.h"
#include "engine/Grid.h"
#include "engine/Scene.h"
#include "engine/strategies/AbstractChasingStrategy.h"
#include <QRandomGenerator>
#include <QDebug>

EnemyController::EnemyController(GameObject *parent) :
	AbstractBehavior(parent),
	_state{ST_Scatter},
	_characterMovement{nullptr},
	_player{nullptr},
	_chasingStrategy{nullptr}/*,
	_targetMark{new QGraphicsRectItem()}*/
{
	// _targetMark->setRect(-10, -10, 20, 20);
	// _targetMark->setPen(QPen(Qt::transparent));
	// _targetMark->setBrush(Qt::green);
}

EnemyController::StateType EnemyController::state() const
{
	return _state;
}

void EnemyController::setState(StateType state)
{
	_state = state;
}

GameObject *EnemyController::player() const
{
	return _player;
}

void EnemyController::setPlayer(GameObject *player)
{
	_player = player;
}

QPointF EnemyController::scatterTarget() const
{
	return _scatterTargetPosition;
}

void EnemyController::setScatterTarget(const QPointF &point)
{
	_scatterTargetPosition = point;
}

AbstractChasingStrategy *EnemyController::chasingStrategy() const
{
	return _chasingStrategy;
}

void EnemyController::setChasingStrategy(AbstractChasingStrategy *strategy)
{
	_chasingStrategy = strategy;
}

void EnemyController::setCharacterMovement(CharacterMovement *characterMovement)
{
	_characterMovement = characterMovement;
}

int EnemyController::type() const
{
	return BT_EnemyController;
}

void EnemyController::performActions()
{
	if (!_characterMovement || !_player)
		return;

	// if (!_targetMark->scene())
	// 	_characterMovement->parent()->scene()->addItem(_targetMark);

	const QList<Vector2> &directions{_characterMovement->possibleMoves()};

	if (directions.isEmpty()) {
		_characterMovement->reverse();
		return;
	}

	// ranadom movement
	// int cnt{static_cast<int>(directions.count())};
	// int ind{QRandomGenerator::global()->bounded(0, cnt)};
	// m_characterMovement->setNextMove(directions.at(ind));

	updateTargetPosition();

	qreal dt{distanceToTarget(directions.first())};

	int ind{0};
	int n{1};

	auto lastDirections{directions.last(directions.count() - 1)};

	for (const auto &direction : lastDirections) {
		qreal d{distanceToTarget(direction)};

		if (d < dt) {
			dt = d;
			ind = n;
		}

		n++;
	}

	_characterMovement->setNextDirection(directions.at(ind));

	// _targetMark->setPos(_currentTargetPosition);
}

qreal EnemyController::distanceToTarget(Vector2 direction) const
{
	// TODO - Improve if possible

	return _characterMovement->nextCellPositionIn(direction).distanceTo(Vector2(_currentTargetPosition));
}

void EnemyController::updateTargetPosition()
{
	if (!_chasingStrategy)
		return;

	switch (_state) {
	case ST_Scatter:
		_currentTargetPosition = _scatterTargetPosition;
		break;
	case ST_Chase:
		_currentTargetPosition = _chasingStrategy->calculateTargetPosition();
		break;
	default:
		break;
	}
}
