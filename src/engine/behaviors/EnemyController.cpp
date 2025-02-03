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

	// m_characterMovement->direction();
	// m_characterMovement->

	int d{QRandomGenerator::global()->bounded(0, 3)};

	switch (d) {
	case 0:
		m_characterMovement->setNextMove(Vector2(-1, 0));
		break;
	case 1:
		m_characterMovement->setNextMove(Vector2(1, 0));
		break;
	case 2:
		m_characterMovement->setNextMove(Vector2(0, -1));
		break;
	case 3:
		m_characterMovement->setNextMove(Vector2(0, 1));
		break;
	}
}
