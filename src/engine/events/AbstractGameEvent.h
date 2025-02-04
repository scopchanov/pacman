#ifndef ABSTRACTGAMEEVENT_H
#define ABSTRACTGAMEEVENT_H

#include <QObject>

class AbstractGameEvent : public QObject
{
	Q_OBJECT
public:
	explicit AbstractGameEvent(QObject *parent = nullptr);

	virtual void trigger() = 0;
};

#endif // ABSTRACTGAMEEVENT_H
