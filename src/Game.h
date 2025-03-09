#ifndef GAME_H
#define GAME_H

#include <QObject>

class AbstractGameObject;
class AudioEngine;
class GameStatus;
class GameLevel;
class Clock;
class Grid;
class Palette;
class InputSystem;

class Game : public QObject
{
    Q_OBJECT

	explicit Game(QObject *parent = nullptr);

public:
	GameLevel *level() const;
	Clock *clock() const;
	Palette *palette() const;
	InputSystem *inputSystem() const;
	GameStatus *status() const;

	static Game &ref();

public slots:
	void newGame();
	void start();
	void stop();
	void resume();
	void reset();
	void onDotEaten();
	void onEnemyEaten();
	void onFruitEaten();
	void onPlayerEnergized();
	void onPlayerWon();
	void onPlayerDied();
	void onFuneralTunePlayed();

private:
	void rewardBonusPoints(int points, int sfxIndex);
	void showBonusText(int points, qreal duration);
	void rewardPoints(int points, int sfxIndex);
	void stopGame(int sfxIndex);
	void playSoundEffect(int sfxIndex);

	GameLevel *_level;
	GameStatus *_status;
	AudioEngine *_audioEngine;

signals:
	void playerWins();
	void gameOver();
};

#endif // GAME_H
