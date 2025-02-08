#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QObject>

class QElapsedTimer;
class GameScene;

class GameTimer : public QObject
{
    Q_OBJECT
public:
	explicit GameTimer(QObject *parent = nullptr);
	~GameTimer();

    qreal deltaTime() const;
	void setScene(GameScene *scene);

public slots:
    void start();
	void pause();
    void stop();

private:
	GameScene *_scene;
	QElapsedTimer *_time;
	QTimer *_timer;

private slots:
    void onTimeout();

signals:
	void gameAdvanced();
};

#endif // GAMETIMER_H
