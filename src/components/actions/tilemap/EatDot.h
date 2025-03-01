#ifndef EATDOT_H
#define EATDOT_H

#include "AbstractTilemapAction.h"

class EatDot : public AbstractTilemapAction
{
	Q_OBJECT
public:
	explicit EatDot(AbstractComponent *parent = nullptr);

	int type() const override;

protected:
	void performTasks() override;

private:
	Tilemap *tilemap() const override;

signals:
	void dotEaten();
	void playerWon();
};

#endif // EATDOT_H
