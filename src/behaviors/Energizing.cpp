#include "Energizing.h"
#include "GameGlobals.h"

Energizing::Energizing(AbstractComponent *parent) :
	AbstractBehavior(parent)
{

}

int Energizing::type() const
{
	return BT_Energizing;
}
