#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractCharacter.h"

class Player : public AbstractCharacter
{
public:
	explicit Player(AbstractGameObject *parent = nullptr);
	
	void energize();
	void deenergize();

	int objectType() const override final;

protected:
	int colorRole() const override;

private:
	void mutate(qreal speed, const QColor &color, bool eatEnemy);
	void enableEatEnemy(bool enable);
};

#endif // PLAYER_H
