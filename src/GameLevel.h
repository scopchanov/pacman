#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <Scene.h>

class LevelMode;
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
	void addEnemy(Enemy *enemy);
	QList<Enemy *> enemies() const;
	LevelMode *mode() const;
	Deenergizer *deenergizer() const;

	void reset() override;

private:
	Tilemap *_walls;
	Tilemap *_dots;
	Player *_player;
	QList<Enemy *> _enemies;
	LevelMode *_mode;
	Deenergizer *_deenergizer;
};

#endif // GAMELEVEL_H
