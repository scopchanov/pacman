#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include <QObject>

class GameStatus : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int lifesLeft READ lifesLeft NOTIFY lifesLeftChanged FINAL)
	Q_PROPERTY(int score READ score NOTIFY scoreChanged FINAL)
public:
	explicit GameStatus(QObject *parent = nullptr);

	int lifesLeft() const;
	int score() const;
	void increaseScore(int amount);

	void reset();

public slots:
	void addLife();
	void removeLife();

private:
	int _lifesLeft;
	int _score;

signals:
	void lifesLeftChanged(int value);
	void scoreChanged(int value);
};

#endif // GAMESTATUS_H
