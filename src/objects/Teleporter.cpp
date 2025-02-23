#include "Teleporter.h"
#include "GameGlobals.h"

Teleporter::Teleporter(AbstractGameObject *parent) :
	AbstractGameObject(parent)
{

}

int Teleporter::objectType() const
{
	return OBJ_Teleporter;
}
