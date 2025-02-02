#ifndef ABSTRACTCHARACTERBEHAVIOR_H
#define ABSTRACTCHARACTERBEHAVIOR_H

#include "AbstractBehavior.h"
#include "engine/Vector2.h"

class GameObject;
class GameController;
class Tilemap;

class AbstractCharacterBehavior : public AbstractBehavior
{
public:
	explicit AbstractCharacterBehavior(GameObject *parent = nullptr);

	GameController *gameController() const;
	virtual void setGameController(GameController *gameController);
	Tilemap *tilemap() const;
	virtual void setTilemap(Tilemap *tilemap);

	void execute() override final;

protected:
	virtual void performActions() = 0;
	Vector2 currentCell() const;

private:
	GameController *m_gameController;
	Tilemap *m_tilemap;
};

#endif // ABSTRACTCHARACTERBEHAVIOR_H
