#ifndef ENEMY_H
#define ENEMY_H

#include "AbstractCharacter.h"

class AbstractPersonality;

class Enemy : public AbstractCharacter
{
public:
	enum EnemyState : int {
		ST_Exit = 0,
		ST_Frightened,
		ST_Eaten,
		ST_Global
	};

	explicit Enemy(AbstractGameObject *parent = nullptr);
	~Enemy();

	AbstractPersonality *personality() const;
	void setPersonality(AbstractPersonality *personality);
	EnemyState state() const;
	void setState(EnemyState state);
	QGraphicsRectItem *targetMark() const;
	int objectType() const override final;

	void scare();
	void calmDown();
	void eat();

protected:
	int colorRole() const override;

private:
	void enableOrientateEyes(bool enabled);
	void enableKillPlayer(bool enabled);

	AbstractPersonality *_personality;
	EnemyState _state;
	QGraphicsRectItem *_targetMark;
};

#endif // ENEMY_H
