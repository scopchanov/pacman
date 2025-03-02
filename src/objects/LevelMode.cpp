#include "LevelMode.h"
#include "GameGlobals.h"

LevelMode::LevelMode(AbstractGameObject *parent) :
	AbstractGameObject{parent},
	_step{0}
{
	setFlags(ItemHasNoContents);
}

int LevelMode::step() const
{
	return _step;
}

void LevelMode::setStep(int step)
{
	_step = step;

	qDebug() << _step;
}

void LevelMode::incrementStep()
{
	_step++;

	qDebug() << _step;
}

int LevelMode::objectType() const
{
	return OBJ_Npc;
}
