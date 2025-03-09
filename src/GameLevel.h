#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <Scene.h>

class LevelState;
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

public slots:
	void onDotEaten();

private:
	void createFruit();

	LevelState *_state;
	Tilemap *_walls;
	Tilemap *_dots;
	Player *_player;
	QList<Enemy *> _enemies;
	Deenergizer *_deenergizer;
	int _dotsEaten;

signals:
	void energizedProgressChanged(qreal value);
};

#endif // GAMELEVEL_H
