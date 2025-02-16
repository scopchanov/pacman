#include "FrightenEnemies.h"
#include "engine/Game.h"
#include "engine/Enemy.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/behaviors/CharacterMovement.h"
#include <QGraphicsScene>
#include <QBrush>

FrightenEnemies::FrightenEnemies(AbstractBehavior *parent) :
	AbstractAction{parent}
{

}

int FrightenEnemies::type() const
{
	return ACT_FrightenEnemies;
}

void FrightenEnemies::performTask()
{
	const QList<Enemy *> enemies{game()->enemies()};

	for (auto *enemy : enemies) {
		if (controller(enemy)->state() == EnemyController::ST_Eaten)
			continue;

		controller(enemy)->setState(EnemyController::ST_Frightened);
		movement(enemy)->setSpeed(113.636364375);

		enemy->setBrush(QBrush(0x2962FF));
		enemy->findBehavior(AbstractBehavior::BT_KillPlayer)->setEnabled(false);
	}
}

EnemyController *FrightenEnemies::controller(Enemy *enemy) const
{
	auto *behavior{enemy->findBehavior(AbstractBehavior::BT_EnemyController)};

	return static_cast<EnemyController *>(behavior);
}

CharacterMovement *FrightenEnemies::movement(Enemy *enemy) const
{
	auto *behavior{enemy->findBehavior(AbstractBehavior::BT_CharacterMovement)};

	return static_cast<CharacterMovement *>(behavior);
}
