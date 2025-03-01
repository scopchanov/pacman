#ifndef ABSTRACTTILEMAPACTION_H
#define ABSTRACTTILEMAPACTION_H

#include "AbstractAction.h"

class Tilemap;
class Vector2;

class AbstractTilemapAction : public AbstractAction
{
public:
	explicit AbstractTilemapAction(AbstractComponent *parent = nullptr);

protected:
	virtual Tilemap *tilemap() const = 0;
	Vector2 currentCell() const;
};

#endif // ABSTRACTTILEMAPACTION_H
