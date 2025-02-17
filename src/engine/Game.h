#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <QObject>
#include <QJsonArray>
#include <QSize>

class AbstractPersonality;
class GameStatus;
class AudioEngine;
class GameObject;
class GameScene;
class InputSystem;
class AiStateMachine;
class Tilemap;
class Tile;
class Grid;
class Player;
class Enemy;
class GameClock;
class Vector2;

class Game : public QObject
{
    Q_OBJECT
public:
	explicit Game(QObject *parent = nullptr);

	GameClock *clock() const;
	GameStatus *status() const;
	GameScene *scene() const;
	AiStateMachine *stateMachine() const;
	Grid *grid() const;
	Tilemap *walls() const;
	Tilemap *dots() const;
	Player *player() const;
	QList<Enemy *> enemies() const;

	void start();
	void stop();
	void resume();
	void restart();

private:
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	Tile *createTile(int index, const QPen &pen, const QBrush &brush);
	void reset();

	GameClock *_clock;
	GameStatus *_status;
	GameScene *_scene;
	AudioEngine *_audioEngine;
	Grid *_grid;
	Tilemap *_walls;
	Tilemap *_dots;
	AiStateMachine *_stateMachine;
	Player *_player;
	QList<Enemy *> _enemies;
	QJsonArray _dotMatrix;

private slots:
	void onDotEaten();
	void onEnemyEaten();
	void onPlayerEnergized();
	void onPlayerWins();
	void onPlayerDies();
	void onFuneralTunePlayed();

signals:
	void playerWins();
	void gameOver();

	friend class Player;
	friend class Configurator;
};

#endif // GAME_H
