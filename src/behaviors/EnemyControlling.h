#ifndef ENEMYCONTROLLING_H
#define ENEMYCONTROLLING_H

#include "AbstractControllingBehavior.h"
#include "Vector2.h"
#include <QPointF>

class QGraphicsRectItem;
class Moving;
class Enemy;

class EnemyControlling : public AbstractControllingBehavior
{
public:
	enum GlobalState : int {
		GS_Scatter,
		GS_Chase
	};

	explicit EnemyControlling(AbstractGameObject *parent = nullptr);

	void setGlobalState(GlobalState state);

	void reset() override;

private:
	void performControllingActions() override;
	qreal distanceToTarget(Vector2 direction) const;
	void updateTargetPosition();
	bool isTargetReached();
	void processGlobalState();
	void actFrightened();
	Enemy *parentEnemy();

	GlobalState _globalState;
	QPointF _targetPosition;
};

#endif // ENEMYCONTROLLING_H
