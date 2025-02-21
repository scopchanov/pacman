#ifndef GAME_H
#define GAME_H

#include <QObject>

class QGraphicsScene;
class AbstractPersonality;
class AudioEngine;
class GameObject;
class GamePalette;
class GameScene;
class GameStatus;
class InputSystem;
class AiStateMachine;
class Tilemap;
class Tile;
class Grid;
class Player;
class Enemy;
class GameClock;
class Vector2;
class Deenergizer;

class Game : public QObject
{
    Q_OBJECT

	explicit Game(QObject *parent = nullptr);

public:
	GameClock *clock() const;
	QGraphicsScene *scene() const;
	InputSystem *inputSystem() const;
	GameStatus *status() const;
	GamePalette *palette() const;
	AiStateMachine *stateMachine() const;
	Grid *grid() const;
	Tilemap *walls() const;
	Tilemap *dots() const;
	Player *player() const;
	QList<Enemy *> &enemies();

	static Game &ref();

public slots:
	void start();
	void stop();
	void resume();
	void reset();
	void onDotEaten();
	void onEnemyEaten();
	void onPlayerEnergized();
	void onPlayerWins();
	void onPlayerDies();
	void onFuneralTunePlayed();

private:
	GameClock *_clock;
	GameScene *_scene;
	GameStatus *_status;
	GamePalette *_palette;
	AiStateMachine *_stateMachine;
	AudioEngine *_audioEngine;
	Grid *_grid;
	Tilemap *_walls;
	Tilemap *_dots;
	Player *_player;
	QList<Enemy *> _enemies;
	Deenergizer *_deenergizer;

signals:
	void playerWins();
	void gameOver();
};

#endif // GAME_H
