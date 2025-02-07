#include "AbstractChasingStrategy.h"

AbstractChasingStrategy::AbstractChasingStrategy() :
	_player{nullptr}
{

}

GameObject *AbstractChasingStrategy::player() const
{
	return _player;
}

void AbstractChasingStrategy::setPlayer(GameObject *player)
{
	_player = player;
}
