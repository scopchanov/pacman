#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QSize>

class QSoundEffect;
class GameTimer;
class GameObject;
class Scene;
class Message;
class InputSystem;
class Tilemap;
class Tile;

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

	Scene *scene() const;
	bool configure(const QJsonObject &json);

public slots:
	void start();

private:
	void buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush);
	Tile *createTile(int index, const QPen &pen, const QBrush &brush);
	GameObject *createPlayer(Tilemap *tmLayout, Tilemap *tmDots);
	GameObject *createTeleporter(const QPointF &src, const QPointF &dst);
	void updateMessage();

    GameTimer *m_gameTimer;
	Scene *m_scene;
	Message *m_message;
	int m_countDown;
	QSoundEffect *m_countBeep;

private slots:
	void onStartupTimeout();
	void onHideTimeout();
};

#endif // GAME_H
