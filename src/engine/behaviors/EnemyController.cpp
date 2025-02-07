#include "EnemyController.h"
#include "engine/Vector2.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/GameObject.h"
#include "engine/Tilemap.h"
#include "engine/Grid.h"
#include "engine/personalities/AbstractPersonality.h"
#include <QRandomGenerator>

EnemyController::EnemyController(GameObject *parent) :
	AbstractBehavior(parent),
	_state{ST_Exit},
	_personality{nullptr},
	_characterMovement{nullptr},
	_player{nullptr}
{

}

EnemyController::StateType EnemyController::state() const
{
	return _state;
}

void EnemyController::setState(StateType state)
{
	// _state = state;
}

AbstractPersonality *EnemyController::personality() const
{
	return _personality;
}

void EnemyController::setPersonality(AbstractPersonality *personality)
{
	_personality = personality;
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

QPointF EnemyController::scatterTarget() const
{
	return _scatterTargetPosition;
}

void EnemyController::setScatterTarget(const QPointF &point)
{
	_scatterTargetPosition = point;
}

int EnemyController::type() const
{
	return BT_EnemyController;
}

void EnemyController::performActions()
{
	// TODO - Imporve me

	if (!_characterMovement || !_player)
		return;

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
	// TODO - Improve me

	return _characterMovement->nextCellPositionIn(direction).distanceTo(Vector2(_targetPosition));
}

void EnemyController::updateTargetPosition()
{
	if (!_personality)
		return;

	switch (_state) {
	case ST_Exit:
		_targetPosition = QPointF(360, 300);
		break;
	case ST_Scatter:
		_targetPosition = _scatterTargetPosition;
		break;
	case ST_Chase:
		_targetPosition = _personality->calculateTargetPosition();
		break;
	default:
		break;
	}
}
