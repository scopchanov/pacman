#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

class GameTimer;

class GameController : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int lifesLeft READ lifesLeft NOTIFY lifesLeftChanged FINAL)
	Q_PROPERTY(int score READ score NOTIFY scoreChanged FINAL)
public:
	explicit GameController(QObject *parent = nullptr);

	GameTimer *gameTimer() const;

	int lifesLeft() const;
	int score() const;
	void increaseScore(int amount);


public slots:
	void addLife();
	void removeLife();
	void start();

private:
	GameTimer *_gameTimer;
	int _lifesLeft;
	int _score;

signals:
	void lifesLeftChanged(int value);
	void scoreChanged(int value);
};

#endif // GAMECONTROLLER_H
