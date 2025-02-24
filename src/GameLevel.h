#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <Scene.h>

class Clock;
class Palette;
class Grid;
class Tilemap;
class Player;
class Enemy;
class Deenergizer;

class GameLevel : public Scene
{
public:
	explicit GameLevel(QObject *parent = nullptr);

	Tilemap *walls() const;
	Tilemap *dots() const;
	Player *player() const;
	QList<Enemy *> &enemies();
	Deenergizer *deenergizer() const;

private:
	Tilemap *_walls;
	Tilemap *_dots;
	Player *_player;
	QList<Enemy *> _enemies;
	Deenergizer *_deenergizer;
};

#endif // GAMELEVEL_H
