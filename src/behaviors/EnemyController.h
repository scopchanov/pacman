#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "AbstractBehavior.h"
#include "Vector2.h"
#include <QPointF>

class QGraphicsRectItem;
class CharacterMovement;
class Enemy;
class Grid;

class EnemyController : public AbstractBehavior
{
public:
	enum GlobalState : int {
		GS_Scatter,
		GS_Chase
	};

	explicit EnemyController(Enemy *parent = nullptr);

	void setGlobalState(GlobalState state);
	void setCharacterMovement(CharacterMovement *characterMovement);
	Grid *grid() const;
	void setGrid(Grid *grid);
	int type() const override;

	void reset() override;

private:
	void performActions() override;
	qreal distanceToTarget(Vector2 direction) const;
	void updateTargetPosition();
	bool isTargetReached();
	void processGlobalState();
	void actFrightened();
	Enemy *parentEnemy();

	GlobalState _globalState;
	Grid *_grid;
	CharacterMovement *_characterMovement;
	QGraphicsRectItem *_targetMark;
	QPointF _targetPosition;
};

#endif // ENEMYCONTROLLER_H
