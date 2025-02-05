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

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

	GameController *gameController() const;
	Scene *scene() const;

	void configure(const QJsonObject &json);

public slots:
	void start();

private:
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	Tile *createTile(int index, const QPen &pen, const QBrush &brush);
	GameObject *createPlayer(Tilemap *tmLayout, Tilemap *tmDots);
	GameObject *createEnemy(Tilemap *tmLayout, GameObject *player, const QPointF &position, const QString &color, const QPointF &scatterTarget);
	GameObject *createTeleporter(const QPointF &src, const QPointF &dst);

	GameController *m_gameController;
	SoundEngine *m_soundEngine;
	Scene *m_scene;

private slots:
	void onPointEaten();
	void onPlayerWins();
	void onPlayerDies();
};

#endif // GAME_H
