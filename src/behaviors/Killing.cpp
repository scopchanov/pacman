#include "Killing.h"
#include "GameGlobals.h"

Killing::Killing(AbstractComponent *parent) :
	AbstractBehavior(parent)
{

}

int Killing::type() const
{
	return BT_Killing;
}
