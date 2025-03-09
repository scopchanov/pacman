#include "OrientatePlayer.h"
#include "AbstractGameObject.h"
#include "components/actions/tilemap/Move.h"

OrientatePlayer::OrientatePlayer(AbstractComponent *parent) :
	AbstractOrientate(parent)
{

}

void OrientatePlayer::reset()
{
	orientate();
}

void OrientatePlayer::orientate()
{
	const Vector2 &currentDirection{move()->currentDirection()};
	qreal x{currentDirection.x()};
	qreal y{currentDirection.y()};

	transformObject(-x, 1, 0) || transformObject(1, -y, 90);
}

bool OrientatePlayer::transformObject(qreal x, qreal y, qreal angle)
{
	if (!x || !y)
		return false;

	gameObject()->setRotation(angle);
	gameObject()->setTransform(QTransform::fromScale(x, y));

	return true;
}
