#include "Energizing.h"
#include "engine/GameEvent.h"
#include "engine/GameObject.h"
#include "engine/behaviors/Coloring.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/behaviors/CharacterMovement.h"
#include <QBrush>
#include <QTimer>
#include <QGraphicsScene>

Energizing::Energizing(GameObject *parent) :
	AbstractBehavior(parent),
	_player{nullptr},
	_eventPlayerEnergized{nullptr}
{

}

GameObject *Energizing::player() const
{
	return _player;
}

void Energizing::setPlayer(GameObject *player)
{
	_player = player;
}

void Energizing::addEnemy(GameObject *enemy)
{
	if (_enemies.contains(enemy))
		return;

	_enemies.append(enemy);
}

void Energizing::setEvent(GameEvent *event)
{
	_eventPlayerEnergized = event;
}

int Energizing::type() const
{
	return BT_Energizing;
}

void Energizing::performActions()
{
	// TODO: Improve me

	if (!_player || _enemies.isEmpty() || !_eventPlayerEnergized)
		return;

	if (!parent()->collidesWithItem(_player))
		return;

	_player->setBrush(QBrush(0xE040FB));
	_player->findBehavior(BT_EnemyEating)->setEnabled(true);
	_eventPlayerEnergized->trigger();

	auto *timer{new QTimer()};

	timer->setSingleShot(true);
	timer->start(6000);

	QObject::connect(timer, &QTimer::timeout, [this](){
		// enemy->findBehavior(BT_KillPlayer)->setEnabled(true);
		_player->setBrush(Qt::white);
		_player->findBehavior(BT_EnemyEating)->setEnabled(false);

		for (auto *enemy : std::as_const(_enemies)) {
			auto *behaviour{enemy->findBehavior(BT_EnemyController)};
			auto *controller{static_cast<EnemyController *>(behaviour)};

			if (controller->state() == EnemyController::ST_Eaten)
				continue;

			controller->setState(EnemyController::ST_Global);
			enemy->setBrush(static_cast<Coloring *>(enemy->findBehavior(BT_Coloring))->color());
			enemy->findBehavior(BT_KillPlayer)->setEnabled(true);
			static_cast<CharacterMovement *>(enemy->findBehavior(BT_CharacterMovement))->setMovingSpeed(170.4545465625);
		}
	});

	for (auto *enemy : std::as_const(_enemies)) {
		auto *behaviour{enemy->findBehavior(BT_EnemyController)};
		auto *controller{static_cast<EnemyController *>(behaviour)};

		if (controller->state() == EnemyController::ST_Eaten)
			continue;

		controller->setState(EnemyController::ST_Frightened);
		enemy->setBrush(QBrush(0x2962FF));
		enemy->findBehavior(BT_KillPlayer)->setEnabled(false);
		static_cast<CharacterMovement *>(enemy->findBehavior(BT_CharacterMovement))->setMovingSpeed(113.636364375);
	}

	if (parent()->scene())
		parent()->scene()->removeItem(parent());

	// TODO: Safely delete the game object

	// delete parent();
}
