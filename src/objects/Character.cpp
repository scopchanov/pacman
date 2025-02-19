#include "Character.h"
#include "GameGlobals.h"
#include "behaviors/CharacterMovement.h"
#include <QPen>

Character::Character(GameObject *parent) :
	GameObject(parent)
{
	// QPainterPath p;

	// p.addEllipse(-12, -12, 24, 24);

	// setPath(p);
	// setPen(QPen(Qt::transparent));
	// setBrush(Qt::gray);
}

QPointF Character::spawnPosition() const
{
	return _spawnPosition;
}

void Character::setSpawnPosition(const QPointF &point)
{
	_spawnPosition = point;

	respawn();
}

void Character::setSpeed(qreal percent)
{
	auto *behavior{findBehavior(BT_CharacterMovement)};
	qreal originalSpeed{75.75757625};
	qreal nominalSpeed{3*originalSpeed};
	qreal speed{percent*nominalSpeed*0.01};

	static_cast<CharacterMovement *>(behavior)->setSpeed(speed);
}

void Character::reset()
{
	respawn();

	GameObject::reset();
}

void Character::respawn()
{
	setPos(_spawnPosition);
}
