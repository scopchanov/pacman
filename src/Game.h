#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QSize>

class GameController;
class SoundEngine;
class GameObject;
class Scene;
class InputSystem;
class Tilemap;
class Tile;
class Grid;
class Pacman;

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

	GameController *gameController() const;
	Scene *scene() const;
	Tilemap *walls() const;
	Tilemap *dots() const;

	void configure(const QJsonObject &json);
	void start();

private:
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	Tile *createTile(int index, const QPen &pen, const QBrush &brush);
	GameObject *createEnemy(const QPointF &position, const QColor &color, const QPointF &scatterTarget, Grid *grid);
	GameObject *createTeleporter(const QPointF &src, const QPointF &dst);

	GameController *_gameController;
	SoundEngine *_soundEngine;
	Scene *_scene;
	Tilemap *_walls;
	Tilemap *_dots;
	Pacman *_pacman;

private slots:
	void onDotEaten();
	void onPlayerWins();
	void onPlayerDies();

	friend class Player;
};

#endif // GAME_H
