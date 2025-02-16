#ifndef GAMECLOCK_H
#define GAMECLOCK_H

#include <QObject>

class QElapsedTimer;
class GameScene;

class GameClock : public QObject
{
    Q_OBJECT
public:
	explicit GameClock(QObject *parent = nullptr);
	~GameClock();

    qreal deltaTime() const;

public slots:
    void start();
    void stop();
	void onTimeout();

private:
	GameScene *_scene;
	QElapsedTimer *_time;
	QTimer *_timer;

private slots:

signals:
	void tick();
};

#endif // GAMECLOCK_H
