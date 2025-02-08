#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QSize>

class GameController;
class SoundEngine;
class GameObject;
class GameScene;
class InputSystem;
class Tilemap;
class Tile;
class Grid;
class Pacman;
class Vector2;

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = nullptr);

	GameController *gameController() const;
	GameScene *scene() const;
	Grid *grid() const;
	Tilemap *walls() const;
	Tilemap *dots() const;

	void configure(const QJsonObject &json);
	void start();

private:
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	Tile *createTile(int index, const QPen &pen, const QBrush &brush);
	GameObject *createEnemy(const QPointF &position, const QColor &color, const Vector2 &scatterTargetCell);
	GameObject *createTeleporter(const QPointF &src, const QPointF &dst);

	GameController *_gameController;
	SoundEngine *_soundEngine;
	GameScene *_scene;
	Grid *_grid;
	Tilemap *_walls;
	Tilemap *_dots;
	Pacman *_pacman;

private slots:
	void onDotEaten();
	void onPlayerWins();
	void onPlayerDies();

	friend class Player;
};

#endif // GAMEENGINE_H
