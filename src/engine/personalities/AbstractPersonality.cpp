#include "AbstractPersonality.h"

AbstractPersonality::AbstractPersonality(QObject *parent) :
	QObject(parent),
	_player{nullptr}
{

}

GameObject *AbstractPersonality::player() const
{
	return _player;
}

void AbstractPersonality::setPlayer(GameObject *player)
{
	_player = player;
}
