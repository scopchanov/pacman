#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QJsonArray>
#include <QSize>
#include "objects/Player.h"

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
class Deenergizer;

class Game : public QObject
{
    Q_OBJECT

	explicit Game(QObject *parent = nullptr);

public:
	GameClock *clock() const;
	GameStatus *status() const;
	QGraphicsScene *scene() const;
	AiStateMachine *stateMachine() const;
	InputSystem *inputSystem() const;
	Grid *grid() const;
	Tilemap *walls() const;
	Tilemap *dots() const;
	Player *player() const;
	QList<Enemy *> enemies() const;

	void start();
	void stop();
	void resume();
	void restart();

	static Game &ref();

private:
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	QGraphicsPathItem *createTile(int index, const QPen &pen, const QBrush &brush);
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
	Deenergizer *_deenergizer;

public slots:
	void onDotEaten();
	void onEnemyEaten();
	void onPlayerEnergized();
	void onPlayerWins();

private slots:
	void onPlayerDies();
	void onFuneralTunePlayed();

signals:
	void playerWins();
	void gameOver();

	friend class Configurator;
};

#endif // GAME_H
