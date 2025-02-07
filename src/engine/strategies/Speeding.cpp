#include "Speeding.h"
#include "engine/GameObject.h"
#include "engine/Grid.h"
#include "engine/Vector2.h"
#include "engine/behaviors/CharacterMovement.h"

Speeding::Speeding() :
	_grid{nullptr}
{

}

Grid *Speeding::grid() const
{
	return _grid;
}

void Speeding::setGrid(Grid *grid)
{
	_grid = grid;
}

Vector2 Speeding::calculateTargetPosition() const
{
	Vector2 playerCell(_grid->posToCell(player()->pos()));
	auto *behavior{player()->findBehavior(AbstractBehavior::BT_CharacterMovement)};

	if (!behavior)
		return Vector2();

	auto *movement{static_cast<CharacterMovement *>(behavior)};
	const Vector2 &playerDirection(movement->currentDirection());
	const Vector2 &fcbp{playerCell + playerDirection*4};

	return _grid->cellPosition(fcbp);
}
