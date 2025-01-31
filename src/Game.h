#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QSize>

class GameController;
class GameObject;
class Scene;
class InputSystem;
class Tilemap;
class Tile;

class Game : QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

	Scene *scene() const;
	bool config(const QJsonObject &json);
	void start();

private:
	Tilemap *createTilemap(int rows, int columns, const QSizeF &cellSize);
    void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix);
    Tile *createTile(int x, int y);
	GameObject *createPlayer(Tilemap *tmLayout, Tilemap *tmDots);

    GameController *m_controller;
	Scene *m_scene;
};

#endif // GAME_H
