#include "Energizer.h"
#include "GameGlobals.h"

Energizer::Energizer(AbstractGameObject *parent) :
	AbstractGameObject(parent)
{

}

int Energizer::objectType() const
{
	return OBJ_Energizer;
}
