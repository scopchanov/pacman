#include "Deenergizer.h"
#include "engine/Game.h"
#include "engine/actions/CalmDownEnemies.h"
#include "engine/actions/DeenergizePlayer.h"
#include "engine/actions/DeleteGameObject.h"
#include "engine/behaviors/Delaying.h"
#include <QPen>

Deenergizer::Deenergizer(GameObject *parent) :
	GameObject(parent)
{
	auto *deenergizing{new Delaying(this)};
	auto *actDeenergizePlayer{new DeenergizePlayer(deenergizing)};
	auto *actCalmDownEnemies{new CalmDownEnemies(deenergizing)};
	auto *actDelete{new DeleteGameObject(deenergizing)};

	actDelete->setGameObject(this);

	deenergizing->setDuration(6);
	deenergizing->addAction(actDeenergizePlayer);
	deenergizing->addAction(actCalmDownEnemies);
	deenergizing->addAction(actDelete);

	addBehavior(deenergizing);
	setFlag(QGraphicsItem::ItemHasNoContents);
}
