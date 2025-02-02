#ifndef ABSTRACTCHARACTERBEHAVIOR_H
#define ABSTRACTCHARACTERBEHAVIOR_H

#include "AbstractTimedBehavior.h"
#include "engine/Vector2.h"

class GameObject;
class Tilemap;

class AbstractCharacterBehavior : public AbstractTimedBehavior
{
public:
	explicit AbstractCharacterBehavior(GameObject *parent = nullptr);

	Tilemap *tilemap() const;
	virtual void setTilemap(Tilemap *tilemap);

protected:
	Vector2 currentCell() const;

private:
	void performTimedActions() override final;
	virtual void performCharacterActions() = 0;

	Tilemap *m_tilemap;
};

#endif // ABSTRACTCHARACTERBEHAVIOR_H
