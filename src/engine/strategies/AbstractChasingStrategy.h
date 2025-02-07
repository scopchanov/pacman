#ifndef ABSTRACTCHASINGSTRATEGY_H
#define ABSTRACTCHASINGSTRATEGY_H

#include <QObject>

class GameObject;
class Vector2;

class AbstractChasingStrategy
{
public:
	explicit AbstractChasingStrategy();

	GameObject *player() const;
	void setPlayer(GameObject *player);

	virtual Vector2 calculateTargetPosition() const = 0;

private:
	GameObject *_player;
};

#endif // ABSTRACTCHASINGSTRATEGY_H
