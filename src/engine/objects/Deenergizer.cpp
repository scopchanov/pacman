#include "Deenergizer.h"
#include "engine/Game.h"
#include "engine/actions/CalmDownEnemies.h"
#include "engine/actions/DeenergizePlayer.h"
#include "engine/behaviors/Delaying.h"
#include <QPen>

Deenergizer::Deenergizer(GameObject *parent) :
	GameObject(parent)
{
	auto *deenergizing{new Delaying(this)};
	auto *actDeenergizePlayer{new DeenergizePlayer(deenergizing)};
	auto *actCalmDownEnemies{new CalmDownEnemies(deenergizing)};

	deenergizing->setDuration(6);
	deenergizing->addAction(actDeenergizePlayer);
	deenergizing->addAction(actCalmDownEnemies);

	addBehavior(deenergizing);
	setFlag(QGraphicsItem::ItemHasNoContents);
}

void Deenergizer::reset()
{
	findBehavior(AbstractBehavior::BT_Delaying)->reset();
}
