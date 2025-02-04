#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

class GameTimer;

class GameController : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int lifeCount READ lifeCount NOTIFY lifeCountChanged FINAL)
	Q_PROPERTY(int score READ score NOTIFY scoreChanged FINAL)
public:
	explicit GameController(QObject *parent = nullptr);

	GameTimer *gameTimer() const;

	int lifeCount() const;
	int score() const;
	void increaseScore(int amount);


public slots:
	void addLife();
	void removeLife();
	void start();

private:
	GameTimer *m_gameTimer;
	int m_lifeCount;
	int m_score;

signals:
	void lifeCountChanged(int value);
	void scoreChanged(int value);
};

#endif // GAMECONTROLLER_H
