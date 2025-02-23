#include "GameLevel.h"
#include "Grid.h"
#include "Tilemap.h"
#include "objects/Player.h"
#include "objects/Deenergizer.h"

GameLevel::GameLevel(QObject *parent) :
	GameScene{parent},
	_grid{new Grid(this)},
	_walls{new Tilemap()},
	_dots{new Tilemap()},
	_player{new Player()},
	_deenergizer{new Deenergizer()}
{
	addItem(_walls);
	addItem(_dots);
	addItem(_player);
	addItem(_deenergizer);
}

Grid *GameLevel::grid() const
{
	return _grid;
}

Tilemap *GameLevel::walls() const
{
	return _walls;
}

Tilemap *GameLevel::dots() const
{
	return _dots;
}

Player *GameLevel::player() const
{
	return _player;
}

QList<Enemy *> &GameLevel::enemies()
{
	return _enemies;
}

Deenergizer *GameLevel::deenergizer() const
{
	return _deenergizer;
}
