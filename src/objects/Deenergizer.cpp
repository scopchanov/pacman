#include "Deenergizer.h"
#include "GameGlobals.h"
#include "Game.h"
#include "actions/CalmDownEnemies.h"
#include "actions/DeenergizePlayer.h"
#include "behaviors/Delaying.h"
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

	// QPainterPath p;

	// p.addRect(0, 0, 30*24, 24);

	// setPath(p);
	// setBrush(Qt::green);
}

void Deenergizer::reset()
{
	findBehavior(BT_Delaying)->reset();
}

int Deenergizer::objectType() const
{
	return OBJ_Npc;
}
