#ifndef EATDOT_H
#define EATDOT_H

#include <AbstractAction.h>

class Tilemap;
class Vector2;

class EatDot : public AbstractAction
{
	Q_OBJECT
public:
	explicit EatDot(AbstractComponent *parent = nullptr);

	Tilemap *tilemap() const;
	virtual void setTilemap(Tilemap *tilemap);
	int type() const override;

protected:
	void performTasks() override;

private:
	Vector2 currentCell() const;

	Tilemap *_tilemap;

signals:
	void dotEaten();
	void playerWon();
};

#endif // EATDOT_H
