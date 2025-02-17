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

	virtual void setup(Game *game) = 0;
	void reset() override;
	void respawn();

private:
	QPointF _spawnPosition;
};

#endif // CHARACTER_H
