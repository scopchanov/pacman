#include "Enemy.h"
#include "engine/behaviors/Coloring.h"
#include "engine/behaviors/AbstractBehavior.h"
#include "engine/personalities/AbstractPersonality.h"
#include <QBrush>

Enemy::Enemy(GameObject *parent) :
	Character(parent),
	_personality{nullptr},
	_state{ST_Exit}
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

Enemy::StateType Enemy::state() const
{
	return _state;
}

void Enemy::setState(StateType state)
{
	_state = state;
	// _characterMovement->reverse();
}

void Enemy::setup()
{

}

void Enemy::scare()
{
	_state = ST_Frightened;

	setBrush(QBrush(0x2962FF));
	setSpeed(50);
	findBehavior(AbstractBehavior::BT_KillPlayer)->setEnabled(false);
}

void Enemy::calmDown()
{
	_state = ST_Global;

	restoreColor();
	setSpeed(75);
	findBehavior(AbstractBehavior::BT_KillPlayer)->setEnabled(true);
}

void Enemy::eat()
{
	_state = ST_Eaten;

	setBrush(Qt::transparent);
	setSpeed(150);
}

void Enemy::restoreColor()
{
	auto *behavior{findBehavior(AbstractBehavior::BT_Coloring)};

	setBrush(static_cast<Coloring *>(behavior)->color());
}
