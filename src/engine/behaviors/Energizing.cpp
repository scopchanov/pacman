#include "Energizing.h"
#include "engine/GameEvent.h"
#include "engine/GameObject.h"
#include "engine/actions/AbstractAction.h"

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
	if (!parent()->collidesWithItem(_player))
		return;

	findAction(AbstractAction::ACT_EnergizePlayer)->trigger();
	findAction(AbstractAction::ACT_ScareEnemies)->trigger();
	parent()->deleteLater();

	_eventPlayerEnergized->trigger();
}
