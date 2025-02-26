#include "Deenergizer.h"
#include "Event.h"
#include "GameGlobals.h"
#include "Game.h"
#include "PathBuilder.h"
#include "actions/CalmDownEnemies.h"
#include "actions/DeactivateDeenergizer.h"
#include "actions/DeenergizePlayer.h"
#include "behaviors/Delaying.h"
#include <QPen>

Deenergizer::Deenergizer(AbstractGameObject *parent) :
	AbstractGameObject(parent)
{
	auto *deenergizing{new Delaying()};
	auto *actDeenergizePlayer{new DeenergizePlayer(deenergizing)};
	auto *actCalmDownEnemies{new CalmDownEnemies(deenergizing)};
	auto *actDeactivateDeenergizer{new DeactivateDeenergizer(deenergizing)};
	auto *eventTick{new Event()};

	deenergizing->setDuration(6);
	deenergizing->addComponent(actDeenergizePlayer);
	deenergizing->addComponent(actCalmDownEnemies);
	deenergizing->addComponent(actDeactivateDeenergizer);
	deenergizing->setEventTick(eventTick);
	deenergizing->setEnabled(false);

	addBehavior(deenergizing);

	// TODO: Improve me

	updatePath(0);
	setPen(QPen(QBrush(0xFFEA00), 4, Qt::SolidLine, Qt::RoundCap));
	setBrush(Qt::transparent);

	QObject::connect(eventTick, &Event::triggered, [this, eventTick](){
		updatePath((6 - eventTick->property("time").toDouble())*30*24/6.0);
	});
}

void Deenergizer::activate()
{
	modifyBehavior(MOD_Activate);
}

void Deenergizer::deactivate()
{
	modifyBehavior(MOD_Deactivate);
}

void Deenergizer::reset()
{
	modifyBehavior(MOD_Reset);
}

int Deenergizer::objectType() const
{
	return OBJ_Deenergizer;
}

void Deenergizer::modifyBehavior(int t)
{
	auto *deenergizing{findBehavior(BT_Delaying)};

	if (!deenergizing)
		return;

	switch (t) {
	case MOD_Activate:
		deenergizing->setEnabled(true);
		deenergizing->reset();
		break;
	case MOD_Deactivate:
		deenergizing->setEnabled(false);
		setPath(QPainterPath());
		break;
	case MOD_Reset:
		deenergizing->reset();
		break;
	}
}

void Deenergizer::updatePath(qreal value)
{
	setPath(PathBuilder::dynamicObjectPath(OBJ_Deenergizer, value));
	update();
}
