#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class AbstractPersonality;

class Enemy : public Character
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
	int objectType() const override final;

	void scare();
	void calmDown();
	void eat();

private:
	void enableEyesOrientating(bool enabled);
	void enableKilling(bool enabled);
	void restoreColor();

	AbstractPersonality *_personality;
	EnemyState _state;
};

#endif // ENEMY_H
