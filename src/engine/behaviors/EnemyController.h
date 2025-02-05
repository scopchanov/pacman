#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "AbstractBehavior.h"
#include "engine/Vector2.h"
#include <QPointF>

class CharacterMovement;
class QTimer;

class EnemyController : public AbstractBehavior
{
public:
	explicit EnemyController(GameObject *parent = nullptr);

	GameObject *player() const;
	void setPlayer(GameObject *player);
	QPointF scatterTarget() const;
	void setScatterTarget(const QPointF &vector);
	void setCharacterMovement(CharacterMovement *characterMovement);
	int type() const override;

	void foo();


private:
	void performActions() override;
	qreal distanceToTarget(Vector2 direction) const;

	CharacterMovement *m_characterMovement;
	GameObject *m_player;
	QPointF m_scatterTarget;
	QPointF m_target;
	QTimer *m_timer;
	bool m_chasing;
};

#endif // ENEMYCONTROLLER_H
