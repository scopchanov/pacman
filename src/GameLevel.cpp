#include "GameLevel.h"
#include "GameClock.h"
#include "GamePalette.h"
#include "Grid.h"
#include "Tilemap.h"
#include "objects/Player.h"
#include "objects/Deenergizer.h"

GameLevel::GameLevel(QObject *parent) :
	GameScene{parent},
	_clock{new GameClock(this)},
	_palette{new GamePalette(this)},
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

	connect(_clock, &GameClock::tick, this, &GameLevel::makeTurn);
}

GameClock *GameLevel::clock() const
{
	return _clock;
}

GamePalette *GameLevel::palette() const
{
	return _palette;
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
