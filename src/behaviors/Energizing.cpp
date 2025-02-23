#include "Energizing.h"
#include "AbstractAction.h"
#include "Game.h"
#include "GameEvent.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "objects/Player.h"

Energizing::Energizing(GameObject *parent) :
	AbstractBehavior(parent),
	_eventPlayerEnergized{nullptr}
{

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
	if (!parent()->collidesWithObject(Game::ref().level()->player()))
		return;

	findAction(ACT_EnergizePlayer)->trigger();
	findAction(ACT_ScareEnemies)->trigger();
	parent()->deleteLater();

	_eventPlayerEnergized->trigger();
}
