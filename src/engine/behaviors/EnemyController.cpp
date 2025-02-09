#include "EnemyController.h"
#include "engine/Vector2.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/Enemy.h"
#include "engine/Tilemap.h"
#include "engine/Grid.h"
#include "engine/personalities/AbstractPersonality.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include <QPen>

EnemyController::EnemyController(Enemy *parent) :
	AbstractBehavior(parent),
	_state{ST_Exit},
	_characterMovement{nullptr},
	_player{nullptr},
	_grid{nullptr},
	_targetMark{new QGraphicsRectItem(-10, -10, 20, 20)}
{
	_targetMark->setPen(QPen(Qt::transparent));
}

EnemyController::StateType EnemyController::state() const
{
	return _state;
}

void EnemyController::setState(StateType state)
{
	_state = state;
}

void EnemyController::setCharacterMovement(CharacterMovement *characterMovement)
{
	_characterMovement = characterMovement;
}

GameObject *EnemyController::player() const
{
	return _player;
}

void EnemyController::setPlayer(GameObject *player)
{
	_player = player;
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
	_state = ST_Exit;
	_targetPosition = QPointF(360, 300);
}

void EnemyController::performActions()
{
	// TODO: Improve me

	if (!_characterMovement || !_player || !_grid)
		return;

	updateTargetPosition();

	const QList<Vector2> &directions{_characterMovement->possibleMoves()};

	if (directions.isEmpty()) {
		_characterMovement->reverse();
		return;
	}

	// ranadom movement
	// int cnt{static_cast<int>(directions.count())};
	// int ind{QRandomGenerator::global()->bounded(0, cnt)};
	// _characterMovement->setNextMove(directions.at(ind));

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

	if (!_targetMark->scene())
		parent()->scene()->addItem(_targetMark);

	_targetMark->setPos(_targetPosition);
	_targetMark->setBrush(parent()->brush());
	_targetMark->update();
}

qreal EnemyController::distanceToTarget(Vector2 direction) const
{
	// TODO: Improve me

	return _characterMovement->nextCellPositionIn(direction).distanceTo(Vector2(_targetPosition));
}

void EnemyController::updateTargetPosition()
{
	auto *personality{static_cast<Enemy *>(parent())->personality()};

	switch (_state) {
	case ST_Exit:
		_targetPosition = QPointF(360, 300);

		if (hasLeftTheHouse())
			_state = ST_Scatter;
		break;
	case ST_Scatter:
		_targetPosition = personality->scatterTarget();
		break;
	case ST_Chase:
		_targetPosition = personality->calculateTarget();
		break;
	default:
		break;
	}
}

bool EnemyController::hasLeftTheHouse()
{
	const QPoint &parentCell{_grid->posToCell(parent()->pos())};
	const QPoint &targetCell{_grid->posToCell(_targetPosition)};

	return parentCell == targetCell;
}
