#ifndef DOTSEATING_H
#define DOTSEATING_H

#include "AbstractSpatialBehavior.h"
#include <QObject>

class QSoundEffect;
class PointEaten;

class DotsEating : public AbstractSpatialBehavior
{
public:
	explicit DotsEating(GameObject *parent = nullptr);
	~DotsEating();

	PointEaten *pointEaten() const;
	int type() const override;

private:
	void performSpatialActions() override;
	void eatDotIfAvailable();

	PointEaten *m_pointEaten;
	QSoundEffect *m_effectEat;
	QSoundEffect *m_effectWin;
};

#endif // DOTSEATING_H
