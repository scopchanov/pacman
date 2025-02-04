#include "PointEaten.h"

PointEaten::PointEaten(QObject *parent) :
	AbstractGameEvent{parent}
{

}

void PointEaten::trigger()
{
	emit pointEaten();
}
