#ifndef ABSTRACTSPATIALBEHAVIOR_H
#define ABSTRACTSPATIALBEHAVIOR_H

#include "actions/AbstractTimedAction.h"
#include "Vector2.h"

class AbstractGameObject;
class Tilemap;

class AbstractSpatialBehavior : public AbstractTimedAction
{
public:
	explicit AbstractSpatialBehavior(AbstractComponent *parent = nullptr);

	Tilemap *tilemap() const;
	virtual void setTilemap(Tilemap *tilemap);

protected:
	void performTasks() override final;
	Vector2 currentCell() const;

private:
	virtual void performSpatialActions() = 0;

	Tilemap *_tilemap;
};

#endif // ABSTRACTSPATIALBEHAVIOR_H
