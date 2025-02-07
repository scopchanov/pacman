#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "AbstractBehavior.h"
#include "engine/Vector2.h"
#include <QPointF>

class QGraphicsRectItem;
class CharacterMovement;
class AbstractChasingStrategy;

class EnemyController : public AbstractBehavior
{
public:
	enum StateType : int {
		ST_Scatter = 0,
		ST_Chase,
		ST_Frightened,
		ST_Eaten
	};

	explicit EnemyController(GameObject *parent = nullptr);

	StateType state() const;
	void setState(StateType state);

	GameObject *player() const;
	void setPlayer(GameObject *player);
	QPointF scatterTarget() const;
	void setScatterTarget(const QPointF &point);
	AbstractChasingStrategy *chasingStrategy() const;
	void setChasingStrategy(AbstractChasingStrategy *strategy);
	void setCharacterMovement(CharacterMovement *characterMovement);
	int type() const override;

private:
	void performActions() override;
	qreal distanceToTarget(Vector2 direction) const;
	void updateTargetPosition();

	StateType _state;
	CharacterMovement *_characterMovement;
	GameObject *_player;
	QPointF _scatterTargetPosition;
	QPointF _currentTargetPosition;
	AbstractChasingStrategy *_chasingStrategy;
	// QGraphicsRectItem *_targetMark;
};

#endif // ENEMYCONTROLLER_H
