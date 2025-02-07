#include "Poking.h"
#include "engine/GameObject.h"
#include "engine/Grid.h"
#include "engine/Vector2.h"
#include "engine/behaviors/EnemyController.h"

Poking::Poking(QObject *parent) :
	AbstractPersonality(parent)
{

}

GameObject *Poking::enemy() const
{
	return _enemy;
}

void Poking::setEnemy(GameObject *enemy)
{
	_enemy = enemy;
}

Grid *Poking::grid() const
{
	return _grid;
}

void Poking::setGrid(Grid *grid)
{
	_grid = grid;
}

Vector2 Poking::calculateTargetPosition() const
{
	if (!_enemy || !_grid)
		return Vector2();

	auto *behavior{_enemy->findBehavior(AbstractBehavior::BT_EnemyController)};

	if (!behavior)
		return Vector2();

	auto *controller{static_cast<EnemyController *>(behavior)};
	Vector2 scatterTarget{controller->scatterTarget()};
	qreal distance{Vector2(_enemy->pos()).distanceTo(player()->pos())};
	qreal maxDistance{8*_grid->cellSize().width()};

	return distance > maxDistance ? Vector2(player()->pos()) : scatterTarget;
}
