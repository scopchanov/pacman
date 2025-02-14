#include "EnemyEating.h"
#include "engine/GameObject.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/behaviors/CharacterMovement.h"
#include <QBrush>
#include <QHash>

EnemyEating::EnemyEating(GameObject *parent) :
	AbstractBehavior(parent),
	_enemiesEaten{0}
{

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
	const QList<QGraphicsItem *> &collidingItems{parent()->collidingItems()};

	for (auto *item : collidingItems) {
		if (item->type() != GameObject::IT_GameObject)
			continue;

		auto *gameObject{static_cast<GameObject *>(item)};
		auto *behavior{gameObject->findBehavior(BT_EnemyController)};

		if (!behavior)
			continue;

		auto *controller{static_cast<EnemyController *>(behavior)};

		if (controller->state() != EnemyController::ST_Frightened)
			return;

		controller->setState(EnemyController::ST_Eaten);
		gameObject->setBrush(QBrush(Qt::transparent));

		static_cast<CharacterMovement *>(gameObject->findBehavior(BT_CharacterMovement))->setMovingSpeed(300);
	}
}

int EnemyEating::points() const
{
	return QHash<int, int>{{0, 20}, {1, 40}, {2, 80}, {3, 160}}.value(_enemiesEaten);
}
