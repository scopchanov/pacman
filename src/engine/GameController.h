#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

class QGraphicsScene;
class QElapsedTimer;

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = nullptr);
    ~GameController();

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

#endif // GAMECONTROLLER_H
