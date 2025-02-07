#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QObject>

class QElapsedTimer;
class Scene;

class GameTimer : public QObject
{
    Q_OBJECT
public:
	explicit GameTimer(QObject *parent = nullptr);
	~GameTimer();

    qreal deltaTime() const;
	void setScene(Scene *scene);

public slots:
    void start();
	void pause();
    void stop();

private:
	Scene *m_scene;
    QElapsedTimer *m_time;
    QTimer *m_timer;

private slots:
    void onTimeout();

signals:
	void gameAdvanced();
};

#endif // GAMETIMER_H
