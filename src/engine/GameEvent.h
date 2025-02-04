#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <QObject>

class GameEvent : public QObject
{
	Q_OBJECT
public:
	explicit GameEvent(QObject *parent = nullptr);

	void trigger();

signals:
	void triggered();
};

#endif // GAMEEVENT_H
