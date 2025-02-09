#include "Enemy.h"
#include "engine/personalities/AbstractPersonality.h"

Enemy::Enemy(GameObject *parent) :
	Character(parent),
	_personality{nullptr}
{

}

Enemy::~Enemy()
{
	if (_personality)
		delete _personality;
}

AbstractPersonality *Enemy::personality() const
{
	return _personality;
}

void Enemy::setPersonality(AbstractPersonality *personality)
{
	_personality = personality;
	_personality->setParent(this);
}

void Enemy::setup(Game *game)
{

}
