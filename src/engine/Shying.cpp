#include "Shying.h"
#include "GameObject.h"
#include "Grid.h"
#include "behaviors/CharacterMovement.h"
#include "Vector2.h"

Shying::Shying() :
	AbstractChasingStrategy()
{

}

Grid *Shying::grid() const
{
	return _grid;
}

void Shying::setGrid(Grid *grid)
{
	_grid = grid;
}

GameObject *Shying::enemy() const
{
	return _enemy;
}

void Shying::setEnemy(GameObject *enemy)
{
	_enemy = enemy;
}

Vector2 Shying::calculateTargetPosition() const
{
	Vector2 playerCell(_grid->posToCell(player()->pos()));
	auto *behavior{player()->findBehavior(AbstractBehavior::BT_CharacterMovement)};

	if (!behavior)
		return Vector2();

	auto *movement{static_cast<CharacterMovement *>(behavior)};
	const Vector2 &playerDirection(movement->currentDirection());
	const Vector2 &tcbp{playerCell + playerDirection*2};

	return Vector2(_enemy->pos() - _grid->cellPosition(tcbp)).reversed() + Vector2(_grid->cellPosition(tcbp));
}
