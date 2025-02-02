#ifndef ABSTRACTSPATIALBEHAVIOR_H
#define ABSTRACTSPATIALBEHAVIOR_H

#include "AbstractTimedBehavior.h"
#include "engine/Vector2.h"

class GameObject;
class Tilemap;

class AbstractSpatialBehavior : public AbstractTimedBehavior
{
public:
	explicit AbstractSpatialBehavior(GameObject *parent = nullptr);

	Tilemap *tilemap() const;
	virtual void setTilemap(Tilemap *tilemap);

protected:
	Vector2 currentCell() const;

private:
	void performTimedActions() override final;
	virtual void performSpatialActions() = 0;

	Tilemap *m_tilemap;
};

#endif // ABSTRACTSPATIALBEHAVIOR_H
