#include "ActivateDeenergizer.h"
#include "Game.h"
#include "GameGlobals.h"
#include "GameLevel.h"
#include "objects/Deenergizer.h"

ActivateDeenergizer::ActivateDeenergizer(AbstractComponent *parent) :
	AbstractAction(parent)
{

}

int ActivateDeenergizer::type() const
{
	return ACT_ActivateDeenergizer;
}

void ActivateDeenergizer::performTasks()
{

}
