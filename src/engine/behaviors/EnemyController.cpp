#include "EnemyController.h"
#include "engine/AiStateMachine.h"
#include "engine/Enemy.h"
#include "engine/Grid.h"
#include "engine/Tilemap.h"
#include "engine/Vector2.h"
#include "engine/behaviors/Coloring.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/personalities/AbstractPersonality.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include <QPen>

EnemyController::EnemyController(Enemy *parent) :
	AbstractBehavior(parent),
	_state{ST_Exit},
	_globalState{GS_Scatter},
	_grid{nullptr},
	_player{nullptr},
	_characterMovement{nullptr},
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
	_characterMovement->reverse();
}

void EnemyController::setGlobalState(GlobalState state)
{
	_globalState = state;
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
	if (!_characterMovement || !_player || !_grid)
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
	switch (_state) {
	case ST_Exit:
	case ST_Eaten:
		_targetPosition = QPointF(360, 300);

		if (isTargetReached())
			restoreState();
		break;
	case ST_Frightened:
		actFrightened();
		break;
	case ST_Global:
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
	auto *personality{static_cast<Enemy *>(parent())->personality()};

	switch (_globalState) {
	case GS_Scatter:
		_targetPosition = personality->scatterTarget();
		break;
	case GS_Chase:
		_targetPosition = personality->calculateTarget();
		break;
	}
}

void EnemyController::restoreState()
{
	_state = ST_Global;

	parent()->findBehavior(BT_KillPlayer)->setEnabled(true);

	restoreSpeed();
	restoreColor();
}

void EnemyController::restoreSpeed()
{
	auto *behavior{parent()->findBehavior(BT_CharacterMovement)};

	static_cast<CharacterMovement *>(behavior)->setSpeed(170.4545465625);
}

void EnemyController::restoreColor()
{
	auto *behavior{parent()->findBehavior(BT_Coloring)};

	parent()->setBrush(static_cast<Coloring *>(behavior)->color());
}

void EnemyController::actFrightened()
{
	// ranadom movement
	// int cnt{static_cast<int>(directions.count())};
	// int ind{QRandomGenerator::global()->bounded(0, cnt)};
	// _characterMovement->setNextMove(directions.at(ind));
}
