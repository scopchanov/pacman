#ifndef ABSTRACTSPATIALBEHAVIOR_H
#define ABSTRACTSPATIALBEHAVIOR_H

#include "AbstractTimedBehavior.h"
#include "Vector2.h"

class AbstractGameObject;
class Tilemap;

class AbstractSpatialBehavior : public AbstractTimedBehavior
{
public:
	explicit AbstractSpatialBehavior(AbstractGameObject *parent = nullptr);

	Tilemap *tilemap() const;
	virtual void setTilemap(Tilemap *tilemap);

protected:
	Vector2 currentCell() const;

private:
	void performActions() override final;
	virtual void performSpatialActions() = 0;

	Tilemap *_tilemap;
};

#endif // ABSTRACTSPATIALBEHAVIOR_H
