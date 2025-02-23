#ifndef GAME_H
#define GAME_H

#include <QObject>

class AbstractPersonality;
class AudioEngine;
class GameLevel;
class AbstractGameObject;
class Palette;
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
	GameLevel *level() const;
	GameClock *clock() const;
	Palette *palette() const;
	InputSystem *inputSystem() const;
	GameStatus *status() const;
	AiStateMachine *stateMachine() const;

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
	GameLevel *_level;
	GameStatus *_status;
	AiStateMachine *_stateMachine;
	AudioEngine *_audioEngine;

signals:
	void playerWins();
	void gameOver();
};

#endif // GAME_H
