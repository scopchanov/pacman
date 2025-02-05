#include "EnemyController.h"
#include "engine/Vector2.h"
#include "engine/behaviors/CharacterMovement.h"
#include <QRandomGenerator>
#include <QDebug>

EnemyController::EnemyController(GameObject *parent) :
	AbstractBehavior(parent),
	m_characterMovement{nullptr}
{
}

void EnemyController::setCharacterMovement(CharacterMovement *characterMovement)
{
	m_characterMovement = characterMovement;
}

int EnemyController::type() const
{
	return BT_EnemyController;
}

void EnemyController::performActions()
{
	if (!m_characterMovement)
		return;


	const QList<Vector2> &directions{m_characterMovement->possibleMoves()};

	if (directions.isEmpty()) {
		m_characterMovement->reverse();
		return;
	}

	int cnt{static_cast<int>(directions.count())};
	int ind{QRandomGenerator::global()->bounded(0, cnt)};

	m_characterMovement->setNextMove(directions.at(ind));
}
