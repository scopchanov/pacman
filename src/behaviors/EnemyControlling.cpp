#include "EnemyControlling.h"
#include "Game.h"
#include "GameLevel.h"
#include "Grid.h"
#include "AiStateMachine.h"
#include "behaviors/Moving.h"
#include "objects/Enemy.h"
#include "personalities/AbstractPersonality.h"
#include <QGraphicsScene>
#include <QRandomGenerator>

EnemyControlling::EnemyControlling(AbstractGameObject *parent) :
	AbstractControllingBehavior(parent),
	_globalState{GS_Scatter}
{

}

void EnemyControlling::setGlobalState(GlobalState state)
{
	_globalState = state;
}

void EnemyControlling::reset()
{
	parentEnemy()->setState(Enemy::ST_Exit);
	_targetPosition = QPointF(360, 300);
}

void EnemyControlling::performControllingActions()
{
	updateTargetPosition();

	const QList<Vector2> &directions{moving()->possibleMoves()};

	if (directions.isEmpty()) {
		moving()->reverse();
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

	moving()->setNextDirection(directions.at(index));
}

qreal EnemyControlling::distanceToTarget(Vector2 direction) const
{
	// TODO: Improve me

	return moving()->nextCellPositionIn(direction).distanceTo(Vector2(_targetPosition));
}

void EnemyControlling::updateTargetPosition()
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

bool EnemyControlling::isTargetReached()
{
	auto *grid{Game::ref().level()->grid()};
	const QPoint &parentCell{grid->mapToGrid(parent()->pos())};
	const QPoint &targetCell{grid->mapToGrid(_targetPosition)};

	return parentCell == targetCell;
}

void EnemyControlling::processGlobalState()
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

void EnemyControlling::actFrightened()
{
	// ranadom movement
	// int cnt{static_cast<int>(directions.count())};
	// int ind{QRandomGenerator::global()->bounded(0, cnt)};
	// _moving->setNextMove(directions.at(ind));
}

Enemy *EnemyControlling::parentEnemy()
{
	return static_cast<Enemy *>(parent());
}
