#include "Deenergizer.h"
#include "GameGlobals.h"
#include "Game.h"
#include "PathBuilder.h"
#include "components/actions/CalmDownEnemies.h"
#include "components/actions/DeactivateDeenergizer.h"
#include "components/actions/DeenergizePlayer.h"
#include "components/behaviors/Delaying.h"
#include <QPen>

Deenergizer::Deenergizer(AbstractGameObject *parent) :
	AbstractGameObject(parent)
{
	auto *deenergizing{new Delaying()};
	auto *actDeenergizePlayer{new DeenergizePlayer(deenergizing)};
	auto *actCalmDownEnemies{new CalmDownEnemies(deenergizing)};
	auto *actDeactivateDeenergizer{new DeactivateDeenergizer(deenergizing)};

	deenergizing->setDuration(6);
	deenergizing->addComponent(actDeenergizePlayer);
	deenergizing->addComponent(actCalmDownEnemies);
	deenergizing->addComponent(actDeactivateDeenergizer);
	deenergizing->setEnabled(false);

	addComponent(deenergizing);

	updatePath(0);
	setPen(QPen(QBrush(0xFFEA00), 4, Qt::SolidLine, Qt::RoundCap));
	setBrush(Qt::transparent);

	QObject::connect(deenergizing, &Delaying::tick, [this](qreal time){
		updatePath((6 - time)*30*24/6.0);
	});
}

void Deenergizer::activate()
{
	modifyComponent(MOD_Activate);
}

void Deenergizer::deactivate()
{
	modifyComponent(MOD_Deactivate);
}

void Deenergizer::reset()
{
	modifyComponent(MOD_Reset);
}

int Deenergizer::objectType() const
{
	return OBJ_Deenergizer;
}

void Deenergizer::modifyComponent(int t)
{
	auto *deenergizing{findComponent(BT_Delaying)};

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
