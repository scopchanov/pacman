#include "Deenergizer.h"
#include "engine/actions/CalmDownEnemies.h"
#include "engine/actions/DeenergizePlayer.h"
#include "engine/actions/DeleteGameObject.h"
#include "engine/behaviors/Delaying.h"
#include "engine/behaviors/EnemyController.h"

Deenergizer::Deenergizer(GameObject *parent) :
	GameObject(parent)
{
	// auto *deenergizing{new Delaying(parent)};
	// auto *actDeenergizePlayer{new DeenergizePlayer(deenergizing)};
	// auto *actCalmDownEnemies{new CalmDownEnemies(deenergizing)};
	// auto *actDeleteDeenergizer{new DeleteGameObject(deenergizing)};

	// actDeenergizePlayer->setGame(this);
	// actCalmDownEnemies->setGame(this);
	// actDeleteDeenergizer->setGame(this);
	// actDeleteDeenergizer->setGameObject(deenergizer);

	// deenergizing->setDuration(6);
	// deenergizing->setClock(_clock);
	// deenergizing->addAction(actDeenergizePlayer);
	// deenergizing->addAction(actCalmDownEnemies);
	// deenergizing->addAction(actDeleteDeenergizer);

	// deenergizer->addBehavior(deenergizing);
	// deenergizer->setFlag(QGraphicsItem::ItemHasNoContents);
}
