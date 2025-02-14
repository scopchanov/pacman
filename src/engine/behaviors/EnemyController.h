#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "AbstractBehavior.h"
#include "engine/Vector2.h"
#include <QPointF>

class QGraphicsRectItem;
class CharacterMovement;
class Enemy;
class Grid;

class EnemyController : public AbstractBehavior
{
public:
	enum StateType : int {
		ST_Exit = 0,
		ST_Frightened,
		ST_Eaten,
		ST_Global
	};

	enum GlobalState : int {
		GS_Scatter,
		GS_Chase
	};

	explicit EnemyController(Enemy *parent = nullptr);

	StateType state() const;
	void setState(StateType state);
	void setGlobalState(GlobalState state);
	void setCharacterMovement(CharacterMovement *characterMovement);
	GameObject *player() const;
	void setPlayer(GameObject *player);
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
	void restoreState();
	void restoreSpeed();
	void restoreColor();
	void actFrightened();

	StateType _state;
	GlobalState _globalState;
	Grid *_grid;
	GameObject *_player;
	CharacterMovement *_characterMovement;
	QGraphicsRectItem *_targetMark;
	QPointF _targetPosition;
};

#endif // ENEMYCONTROLLER_H
