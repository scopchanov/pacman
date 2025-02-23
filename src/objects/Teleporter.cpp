#include "Teleporter.h"
#include "GameGlobals.h"

Teleporter::Teleporter(GameObject *parent) :
	GameObject(parent)
{

}

int Teleporter::objectType() const
{
	return OBJ_Teleporter;
}
