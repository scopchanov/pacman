#ifndef GAME_H
#define GAME_H

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
class Pacman;
class Ghost;
class PowerUp;

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

	void start();
	void stop();
	void resume();
	void restart();

private:

	void reset();

	GameClock *_clock;
	GameStatus *_status;
	GameScene *_scene;
	AudioEngine *_audioEngine;
	Grid *_grid;
	Tilemap *_walls;
	Tilemap *_dots;
	AiStateMachine *_stateMachine;
	Pacman *_pacman;
	QList<Ghost *> _ghosts;
	QJsonArray _dotMatrix;

private slots:
	void onDotEaten();
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
