#include "Energizing.h"
#include "Game.h"
#include "Event.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "objects/Player.h"

Energizing::Energizing(AbstractComponent *parent) :
	AbstractBehavior(parent),
	_eventPlayerEnergized{nullptr}
{

}

void Energizing::setEvent(Event *event)
{
	_eventPlayerEnergized = event;
}

int Energizing::type() const
{
	return BT_Energizing;
}

void Energizing::performTasks()
{
	if (!gameObject()->collidesWithObject(Game::ref().level()->player()))
		return;

	// for (auto *action : actions)
	findComponent(ACT_EnergizePlayer)->execute();
	findComponent(ACT_ScareEnemies)->execute();
	findComponent(ACT_ActivateDeenergizer)->execute();
	gameObject()->deleteLater();

	_eventPlayerEnergized->trigger();
}
