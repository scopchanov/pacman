#include "EnableDeenergizer.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "objects/Deenergizer.h"

EnableDeenergizer::EnableDeenergizer(AbstractComponent *parent) :
	AbstractAction(parent)
{

}

int EnableDeenergizer::type() const
{
	return ACT_ActivateDeenergizer;
}

void EnableDeenergizer::performTasks()
{
	Game::ref().level()->deenergizer()->activate();
}
