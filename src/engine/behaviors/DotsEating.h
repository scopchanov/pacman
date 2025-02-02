#ifndef DOTSEATING_H
#define DOTSEATING_H

#include "AbstractCharacterBehavior.h"

class QSoundEffect;

class DotsEating : public AbstractCharacterBehavior
{
public:
	explicit DotsEating(GameObject *parent = nullptr);
	~DotsEating();

private:
	void performCharacterActions() override;
	void eatDotIfAvailable();

	QSoundEffect *m_effectEat;
	QSoundEffect *m_effectWin;
};

#endif // DOTSEATING_H
