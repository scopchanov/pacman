#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>

class AbstractAction;
class AbstractControllingBehavior;
class AbstractOrientate;
class AbstractPersonality;

class Factory : public QObject
{
	Q_OBJECT
public:
	explicit Factory(QObject *parent = nullptr);

	static AbstractAction *createAnimating(int type);
	static AbstractControllingBehavior *createControlling(int type);
	static AbstractOrientate *createOrientating(int type);
	static AbstractPersonality *createPersonality(int type);
};

#endif // FACTORY_H
