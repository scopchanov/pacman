#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class AbstractPersonality;

class Enemy : public Character
{
public:
	enum StateType : int {
		ST_Exit = 0,
		ST_Frightened,
		ST_Eaten,
		ST_Global
	};

	explicit Enemy(GameObject *parent = nullptr);
	~Enemy();

	AbstractPersonality *personality() const;
	void setPersonality(AbstractPersonality *personality);
	StateType state() const;
	void setState(StateType state);
	int objectType() const override final;

	void setup() override;
	void scare();
	void calmDown();
	void eat();

private:
	void restoreColor();

	AbstractPersonality *_personality;
	StateType _state;
};

#endif // ENEMY_H
