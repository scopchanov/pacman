#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <GameScene.h>

class GameClock;
class Palette;
class Grid;
class Tilemap;
class Player;
class Enemy;
class Deenergizer;

class GameLevel : public GameScene
{
public:
	explicit GameLevel(QObject *parent = nullptr);

	GameClock *clock() const;
	Palette *palette() const;
	Grid *grid() const;
	Tilemap *walls() const;
	Tilemap *dots() const;
	Player *player() const;
	QList<Enemy *> &enemies();
	Deenergizer *deenergizer() const;

private:
	GameClock *_clock;
	Palette *_palette;
	Grid *_grid;
	Tilemap *_walls;
	Tilemap *_dots;
	Player *_player;
	QList<Enemy *> _enemies;
	Deenergizer *_deenergizer;
};

#endif // GAMELEVEL_H
