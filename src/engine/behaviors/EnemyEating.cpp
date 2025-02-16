#include "EnemyEating.h"
#include "engine/GameEvent.h"
#include "engine/GameObject.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/behaviors/CharacterMovement.h"
#include <QBrush>
#include <QHash>

EnemyEating::EnemyEating(GameObject *parent) :
	AbstractBehavior(parent),
	_enemiesEaten{0},
	_eventEnemyEaten{nullptr}
{

}

void EnemyEating::setEvent(GameEvent *event)
{
	_eventEnemyEaten = event;
}

int EnemyEating::type() const
{
	return BT_EnemyEating;
}

void EnemyEating::reset()
{
	_enemiesEaten = 0;
}

void EnemyEating::performActions()
{
	if (!_eventEnemyEaten)
		return;

	const QList<QGraphicsItem *> &collidingItems{parent()->collidingItems()};

	for (auto *item : collidingItems) {
		if (item->type() != GameObject::IT_GameObject)
			continue;

		auto *enemy{static_cast<GameObject *>(item)};
		auto *behavior{enemy->findBehavior(BT_EnemyController)};

		if (!behavior)
			continue;

		auto *controller{static_cast<EnemyController *>(behavior)};

		if (controller->state() != EnemyController::ST_Frightened)
			return;

		eatEnemy(enemy);
	}
}

void EnemyEating::eatEnemy(GameObject *enemy)
{
	auto *behavior{enemy->findBehavior(BT_EnemyController)};
	auto *controller{static_cast<EnemyController *>(behavior)};

	controller->setState(EnemyController::ST_Eaten);
	enemy->setBrush(QBrush(Qt::transparent));

	speedUpMovement(enemy);

	_eventEnemyEaten->setProperty("points", points());
	_eventEnemyEaten->trigger();

	_enemiesEaten++;

	if (_enemiesEaten >= 4)
		_enemiesEaten = 0;
}

void EnemyEating::speedUpMovement(GameObject *enemy)
{
	auto *behavior{enemy->findBehavior(BT_CharacterMovement)};

	static_cast<CharacterMovement *>(behavior)->setSpeed(300);
}

int EnemyEating::points() const
{
	return QHash<int, int>{{0, 20}, {1, 40}, {2, 80}, {3, 160}}.value(_enemiesEaten);
}
