#include "PoweringUp.h"
#include "engine/GameObject.h"
#include "engine/behaviors/EnemyController.h"
#include <QBrush>

PoweringUp::PoweringUp(GameObject *parent) :
	AbstractBehavior(parent),
	_player{nullptr}
{

}

GameObject *PoweringUp::player() const
{
	return _player;
}

void PoweringUp::setPlayer(GameObject *player)
{
	_player = player;
}

void PoweringUp::addEnemy(GameObject *enemy)
{
	if (_enemies.contains(enemy))
		return;

	_enemies.append(enemy);
}

int PoweringUp::type() const
{
	return BT_PoweringUp;
}

void PoweringUp::performActions()
{
	if (!_player || _enemies.isEmpty())
		return;

	if (!parent()->collidesWithItem(_player))
		return;

	_player->setBrush(Qt::yellow);
	_player->findBehavior(BT_EnemyEating)->setEnabled(true);

	for (auto *enemy : std::as_const(_enemies)) {
		auto *behaviour{enemy->findBehavior(BT_EnemyController)};
		auto *controller{static_cast<EnemyController *>(behaviour)};

		if (controller->state() == EnemyController::ST_Eaten)
			continue;

		controller->setState(EnemyController::ST_Frightened);
		enemy->setBrush(QBrush(0x2962FF));
		enemy->findBehavior(BT_KillPlayer)->setEnabled(false);
	}

	delete parent();
}
