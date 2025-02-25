#include "Deenergizer.h"
#include "Event.h"
#include "GameGlobals.h"
#include "Game.h"
#include "actions/CalmDownEnemies.h"
#include "actions/DeenergizePlayer.h"
#include "behaviors/Delaying.h"
#include <QPen>

Deenergizer::Deenergizer(AbstractGameObject *parent) :
	AbstractGameObject(parent)
{
	auto *deenergizing{new Delaying(this)};
	auto *actDeenergizePlayer{new DeenergizePlayer(deenergizing)};
	auto *actCalmDownEnemies{new CalmDownEnemies(deenergizing)};
	auto *eventTick{new Event()};

	deenergizing->setDuration(6);
	deenergizing->addAction(actDeenergizePlayer);
	deenergizing->addAction(actCalmDownEnemies);
	deenergizing->setEventTick(eventTick);

	addBehavior(deenergizing);

	// TODO: Improve me

	QPainterPath p;

	p.addRect(0, 0, 30*24, 6);

	setPath(p);
	setBrush(QBrush(0xFFEA00));

	QObject::connect(eventTick, &Event::triggered, [this, eventTick](){
		qreal a{6 - eventTick->property("time").toDouble()};

		QPainterPath p;

		p.addRect(0, 0, a*100, 6);

		setPath(p);
	});
}

void Deenergizer::reset()
{
	auto *delaing{findBehavior(BT_Delaying)};

	if (delaing)
		delaing->reset();
}

int Deenergizer::objectType() const
{
	return OBJ_Npc;
}
