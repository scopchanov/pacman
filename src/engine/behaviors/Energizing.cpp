#include "Energizing.h"
#include "engine/GameEvent.h"
#include "engine/GameObject.h"
#include "engine/AbstractAction.h"

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
	// TODO: Execute once

	if (!parent()->collidesWithItem(_player))
		return;

	findAction(AbstractAction::ACT_EnergizePlayer)->trigger();
	findAction(AbstractAction::ACT_FrightenEnemies)->trigger();

	_eventPlayerEnergized->trigger();

	// TODO: Safely delete the game object instead of disabling it

	setEnabled(false);

	parent()->findBehavior(AbstractBehavior::BT_Animation)->setEnabled(false);
	parent()->setFlag(QGraphicsItem::ItemHasNoContents);

	// parent()->deleteSelf();
}
