#ifndef CHARACTER_H
#define CHARACTER_H

#include "engine/objects/GameObject.h"

class Game;

class Character : public GameObject
{
public:
	explicit Character(GameObject *parent = nullptr);

	QPointF spawnPosition() const;
	void setSpawnPosition(const QPointF &point);
	void setSpeed(qreal percent);

	virtual void setup() = 0;
	void reset() override;
	void respawn();

private:
	QPointF _spawnPosition;
};

#endif // CHARACTER_H
