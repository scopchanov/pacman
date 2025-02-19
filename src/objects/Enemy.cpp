#include "Enemy.h"
#include "GameGlobals.h"
#include "behaviors/Coloring.h"
#include "personalities/AbstractPersonality.h"
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

Enemy::EnemyState Enemy::state() const
{
	return _state;
}

void Enemy::setState(EnemyState state)
{
	_state = state;
	// _characterMovement->reverse();
}

int Enemy::objectType() const
{
	return OBJ_Enemy;
}

void Enemy::setup()
{

}

void Enemy::scare()
{
	_state = ST_Frightened;

	setBrush(QBrush(0x2962FF));
	setSpeed(50);
	findBehavior(BT_KillPlayer)->setEnabled(false);
}

void Enemy::calmDown()
{
	_state = ST_Global;

	restoreColor();
	setSpeed(75);
	findBehavior(BT_KillPlayer)->setEnabled(true);
}

void Enemy::eat()
{
	_state = ST_Eaten;

	setBrush(Qt::transparent);
	setSpeed(150);
}

void Enemy::restoreColor()
{
	auto *behavior{findBehavior(BT_Coloring)};

	setBrush(static_cast<Coloring *>(behavior)->color());
}
