#include "Teleporting.h"
#include "GameGlobals.h"

Teleporting::Teleporting(AbstractComponent *parent) :
	AbstractBehavior(parent)
{

}

int Teleporting::type() const
{
	return BT_Teleporting;
}
