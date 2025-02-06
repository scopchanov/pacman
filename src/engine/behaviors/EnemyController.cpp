#include "EnemyController.h"
#include "engine/Vector2.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/GameObject.h"
#include "Foo.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

EnemyController::EnemyController(GameObject *parent) :
	AbstractBehavior(parent),
	m_characterMovement{nullptr},
	m_player{nullptr},
	m_timer{new QTimer()},
	m_chasing{false}
{
	auto *foo{new Foo()};

	foo->setFoo(this);

	QObject::connect(m_timer, &QTimer::timeout, foo, &Foo::dodd);

	m_timer->setSingleShot(false);

}

GameObject *EnemyController::player() const
{
	return m_player;
}

void EnemyController::setPlayer(GameObject *player)
{
	m_player = player;
}

QPointF EnemyController::scatterTarget() const
{
	return m_scatterTarget;
}

void EnemyController::setScatterTarget(const QPointF &vector)
{
	m_scatterTarget = vector;
}

void EnemyController::setCharacterMovement(CharacterMovement *characterMovement)
{
	m_characterMovement = characterMovement;
}

int EnemyController::type() const
{
	return BT_EnemyController;
}

void EnemyController::foo()
{
	m_chasing = !m_chasing;
	m_characterMovement->reverse();

	m_timer->setInterval(m_chasing ? 20000 : 7000);
}

void EnemyController::performActions()
{
	if (!m_characterMovement || !m_player)
		return;

	if (!m_timer->isActive())
		m_timer->start(7000);

	const QList<Vector2> &directions{m_characterMovement->possibleMoves()};

	if (directions.isEmpty()) {
		m_characterMovement->reverse();
		return;
	}

	// ranadom movement
	// int cnt{static_cast<int>(directions.count())};
	// int ind{QRandomGenerator::global()->bounded(0, cnt)};
	// m_characterMovement->setNextMove(directions.at(ind));

	m_target = (m_chasing ? m_player->pos() : m_scatterTarget);

	qreal a{distanceToTarget(directions.first())};

	int ind{0};
	int n{1};

	auto lastDirections{directions.last(directions.count() - 1)};

	for (const auto &direction : lastDirections) {
		qreal d{distanceToTarget(direction)};

		if (d < a) {
			a = d;
			ind = n;
		}

		n++;
	}

	m_characterMovement->setNextDirection(directions.at(ind));
}

qreal EnemyController::distanceToTarget(Vector2 direction) const
{
	// TODO - Improve if possible

	return m_characterMovement->nextCellPositionIn(direction).distanceTo(Vector2(m_target));
}
