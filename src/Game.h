#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QJsonArray>
#include <QSize>

class AbstractPersonality;
class GameController;
class SoundEngine;
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
class Vector2;

class Game : public QObject
{
    Q_OBJECT
public:
	explicit Game(QObject *parent = nullptr);

	GameController *gameController() const;
	GameScene *scene() const;
	Grid *grid() const;
	Tilemap *walls() const;
	Tilemap *dots() const;

	void configure(const QJsonObject &json);
	void start();
	void stop();
	void resume();
	void restart();

private:
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	Tile *createTile(int index, const QPen &pen, const QBrush &brush);
	void createEnemies(const QJsonArray &enemies);
	Ghost *createEnemy(const QPointF &position, const QColor &color, int direction);
	GameObject *createPowerUp(const QPoint &cell);
	GameObject *createTeleporter(const QPointF &src, const QPointF &dst);
	AbstractPersonality *createPersonality(int type);
	Vector2 dir2vec(int direction);
	void reset();

	GameController *_gameController;
	SoundEngine *_soundEngine;
	GameScene *_scene;
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
	void playerLoses();

	friend class Player;
};

#endif // GAME_H
