#include "AbstractTilemapAction.h"
#include "Grid.h"
#include "Tilemap.h"
#include "AbstractGameObject.h"
#include "Vector2.h"

AbstractTilemapAction::AbstractTilemapAction(AbstractComponent *parent) :
	AbstractAction(parent)
{

}

Vector2 AbstractTilemapAction::currentCell() const
{
	return Vector2(tilemap()->grid()->mapToGrid(gameObject()->pos()));
}
