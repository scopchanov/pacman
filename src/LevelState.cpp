#include "LevelState.h"
#include "GameGlobals.h"

LevelState::LevelState(AbstractGameObject *parent) :
	AbstractGameObject{parent}
{
	setFlags(ItemHasNoContents);
}

int LevelState::objectType() const
{
	return OBJ_Npc;
}
