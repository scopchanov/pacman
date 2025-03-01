#include "DeactivateDeenergizer.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "objects/Deenergizer.h"

DeactivateDeenergizer::DeactivateDeenergizer(AbstractComponent *parent) :
	AbstractAction(parent)
{

}

int DeactivateDeenergizer::type() const
{
	return ACT_DeactivateDeenergizer;
}

void DeactivateDeenergizer::performTasks()
{
	Game::ref().level()->deenergizer()->deactivate();
}
