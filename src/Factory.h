#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>

class AbstractAction;
class AbstractControl;
class AbstractOrientate;
class AbstractPersonality;

class Factory : public QObject
{
	Q_OBJECT
public:
	explicit Factory(QObject *parent = nullptr);

	static AbstractAction *createAnimate(int type);
	static AbstractControl *createControl(int type);
	static AbstractOrientate *createOrientate(int type);
	static AbstractPersonality *createPersonality(int type);
};

#endif // FACTORY_H
