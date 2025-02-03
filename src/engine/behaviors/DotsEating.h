#ifndef DOTSEATING_H
#define DOTSEATING_H

#include "AbstractSpatialBehavior.h"

class QSoundEffect;

class DotsEating : public AbstractSpatialBehavior
{
public:
	explicit DotsEating(GameObject *parent = nullptr);
	~DotsEating();

	int type() const override;

private:
	void performSpatialActions() override;
	void eatDotIfAvailable();

	QSoundEffect *m_effectEat;
	QSoundEffect *m_effectWin;
};

#endif // DOTSEATING_H
