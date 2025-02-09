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
		ST_Scatter,
		ST_Chase,
		ST_Frightened,
		ST_Eaten
	};

	explicit EnemyController(Enemy *parent = nullptr);

	StateType state() const;
	void setState(StateType state);	
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
	bool hasLeftTheHouse();

	StateType _state;
	CharacterMovement *_characterMovement;
	GameObject *_player;
	Grid *_grid;
	QPointF _targetPosition;
	QGraphicsRectItem *_targetMark;
};

#endif // ENEMYCONTROLLER_H
