#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "AbstractBehavior.h"
#include "engine/Vector2.h"
#include <QPointF>

class QGraphicsRectItem;
class CharacterMovement;
class AbstractPersonality;

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

	explicit EnemyController(GameObject *parent = nullptr);

	StateType state() const;
	void setState(StateType state);
	AbstractPersonality *personality() const;
	void setPersonality(AbstractPersonality *personality);
	void setCharacterMovement(CharacterMovement *characterMovement);
	GameObject *player() const;
	void setPlayer(GameObject *player);
	QPointF scatterTarget() const;
	void setScatterTarget(const QPointF &point);
	int type() const override;

private:
	void performActions() override;
	qreal distanceToTarget(Vector2 direction) const;
	void updateTargetPosition();

	StateType _state;
	AbstractPersonality *_personality;
	CharacterMovement *_characterMovement;
	GameObject *_player;
	QPointF _scatterTargetPosition;
	QPointF _targetPosition;
	// QGraphicsRectItem *_targetMark;
};

#endif // ENEMYCONTROLLER_H
