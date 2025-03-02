#include "ControlEnemy.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "Grid.h"
#include "LevelState.h"
#include "components/actions/ExecuteStateMachine.h"
#include "components/actions/tilemap/Move.h"
#include "objects/Enemy.h"
#include "personalities/AbstractPersonality.h"
#include <QGraphicsScene>
#include <QRandomGenerator>

ControlEnemy::ControlEnemy(AbstractComponent *parent) :
	AbstractControl(parent)
{

}

void ControlEnemy::reset()
{
	parentEnemy()->setState(Enemy::ST_Exit);
	_targetPosition = QPointF(360, 300);
}

void ControlEnemy::control()
{
	updateTargetPosition();

	const QList<Vector2> &directions{move()->possibleMoves()};

	if (directions.isEmpty()) {
		move()->reverse();
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

	move()->setNextDirection(directions.at(index));
}

qreal ControlEnemy::distanceToTarget(Vector2 direction) const
{
	const Vector2 &nextCell{move()->nextCellPositionIn(direction)};

	return nextCell.distanceTo(Vector2(_targetPosition));
}

void ControlEnemy::updateTargetPosition()
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
		processLevelState();
		break;
	default:
		break;
	}
}

bool ControlEnemy::isTargetReached()
{
	auto *grid{Game::ref().level()->grid()};
	const QPoint &parentCell{grid->mapToGrid(gameObject()->pos())};
	const QPoint &targetCell{grid->mapToGrid(_targetPosition)};

	return parentCell == targetCell;
}

void ControlEnemy::processLevelState()
{
	auto *personality{parentEnemy()->personality()};
	auto *levelState{Game::ref().level()->state()};
	auto *component{levelState->findComponent(ACT_ExecuteStateMachine)};
	auto *control{static_cast<ExecuteStateMachine *>(component)};
	int mode{control->step() % 2 ? WM_Chase : WM_Scatter};

	switch (mode) {
	case WM_Scatter:
		_targetPosition = personality->scatterTarget();
		break;
	case WM_Chase:
		_targetPosition = personality->calculateTarget();
		break;
	}
}

void ControlEnemy::actFrightened()
{
	// ranadom movement
	// int cnt{static_cast<int>(directions.count())};
	// int ind{QRandomGenerator::global()->bounded(0, cnt)};
	// _move->setNextMove(directions.at(ind));
}

Enemy *ControlEnemy::parentEnemy()
{
	return static_cast<Enemy *>(gameObject());
}
