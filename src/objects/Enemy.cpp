#include "Enemy.h"
#include "AbstractComponent.h"
#include "Game.h"
#include "GameGlobals.h"
#include "Palette.h"
#include "Vector2.h"
#include "objects/EnemyEye.h"
#include "personalities/AbstractPersonality.h"
#include <QBrush>

Enemy::Enemy(AbstractGameObject *parent) :
	AbstractCharacter(parent),
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
	// _move->reverse();
}

int Enemy::objectType() const
{
	return OBJ_Enemy;
}

void Enemy::scare()
{
	_state = ST_Frightened;

	enableKillPlayer(false);
	enableOrientateEyes(false);
	setBrush(paletteColor(CR_EnemyFrightened));
	setSpeed(50);
}

void Enemy::calmDown()
{
	_state = ST_Global;

	enableKillPlayer(true);
	enableOrientateEyes(true);
	setBrush(paletteColor(colorRole()));
	setSpeed(75);
}

void Enemy::eat()
{
	_state = ST_Eaten;

	enableOrientateEyes(true);
	setBrush(Qt::transparent);
	setSpeed(150);
}

int Enemy::colorRole() const
{
	return _personality ? _personality->colorRole() : -1;
}

void Enemy::enableOrientateEyes(bool enabled)
{
	const QList<AbstractGameObject *> &eyes{findChildObjects(OBJ_EnemyEye)};

	for (auto *eye : eyes) {
		auto *orientate{eye->findComponent(ACT_Orientate)};

		if (!enabled)
			static_cast<EnemyEye *>(eye)->setDirection(V2_ZERO);

		if (orientate)
			orientate->setEnabled(enabled);
	}
}

void Enemy::enableKillPlayer(bool enabled)
{
	auto *killPlayer{findComponent(ACT_KillPlayer)};

	if (killPlayer)
		killPlayer->setEnabled(enabled);
}
