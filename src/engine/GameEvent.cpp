#include "GameEvent.h"

GameEvent::GameEvent(QObject *parent) :
	QObject(parent)
{

}

void GameEvent::trigger()
{
	emit triggered();
}
