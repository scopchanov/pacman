#include "Energizing.h"
#include "AbstractAction.h"
#include "GameEvent.h"
#include "GameGlobals.h"
#include "GameObject.h"

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
	if (!parent()->collidesWithObject(_player))
		return;

	findAction(ACT_EnergizePlayer)->trigger();
	findAction(ACT_ScareEnemies)->trigger();
	parent()->deleteLater();

	_eventPlayerEnergized->trigger();
}
