#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QObject>

class QGraphicsScene;
class QElapsedTimer;

class GameTimer : public QObject
{
    Q_OBJECT
public:
	explicit GameTimer(QObject *parent = nullptr);
	~GameTimer();

    qreal deltaTime() const;
    void setScene(QGraphicsScene *scene);

public slots:
    void start();
    void stop();

private:
    QGraphicsScene *m_scene;
    QElapsedTimer *m_time;
    QTimer *m_timer;

private slots:
    void onTimeout();
};

#endif // GAMETIMER_H
