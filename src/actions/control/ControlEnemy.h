#ifndef CONTROLENEMY_H
#define CONTROLENEMY_H

#include "AbstractControl.h"
#include "Vector2.h"
#include <QPointF>

class QGraphicsRectItem;
class Moving;
class Enemy;

class ControlEnemy : public AbstractControl
{
public:
	enum GlobalState : int {
		GS_Scatter,
		GS_Chase
	};

	explicit ControlEnemy(AbstractComponent *parent = nullptr);

	void setGlobalState(GlobalState state);

	void reset() override;

protected:
	void control() override;

private:
	qreal distanceToTarget(Vector2 direction) const;
	void updateTargetPosition();
	bool isTargetReached();
	void processGlobalState();
	void actFrightened();
	Enemy *parentEnemy();

	GlobalState _globalState;
	QPointF _targetPosition;
};

#endif // CONTROLENEMY_H
