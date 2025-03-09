#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <Scene.h>

class LevelState;
class Clock;
class Palette;
class Grid;
class Tilemap;
class Player;
class Enemy;
class Deenergizer;

class GameLevel : public Scene
{
	Q_OBJECT
public:
	explicit GameLevel(QObject *parent = nullptr);

	Tilemap *walls() const;
	Tilemap *dots() const;
	Player *player() const;
	void addEnemy(Enemy *enemy);
	QList<Enemy *> enemies() const;
	LevelState *state() const;
	Deenergizer *deenergizer() const;

	void reset() override;

private:
	LevelState *_state;
	Tilemap *_walls;
	Tilemap *_dots;
	Player *_player;
	QList<Enemy *> _enemies;
	Deenergizer *_deenergizer;

signals:
	void energizedProgressChanged(qreal value);
};

#endif // GAMELEVEL_H
