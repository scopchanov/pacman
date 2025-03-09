#ifndef CONTROLENEMY_H
#define CONTROLENEMY_H

#include "AbstractControl.h"
#include "Vector2.h"
#include <QPointF>

class QGraphicsRectItem;
class Move;
class Enemy;

class ControlEnemy : public AbstractControl
{
public:
	explicit ControlEnemy(AbstractComponent *parent = nullptr);

	void reset() override;

protected:
	void control() override;

private:
	qreal distanceToTarget(Vector2 direction) const;
	void updateTargetPosition();
	bool isTargetReached();
	void processLevelState();
	void actFrightened();
	Enemy *parentEnemy() const;

	QPointF _targetPosition;
};

#endif // CONTROLENEMY_H
