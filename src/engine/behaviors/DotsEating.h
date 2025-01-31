#ifndef DOTSEATING_H
#define DOTSEATING_H

#include "AbstractCharacterBehavior.h"

class DotsEating : public AbstractCharacterBehavior
{
public:
	explicit DotsEating();

protected:
	void performActions() override;

private:
	void eatDotIfAvailable();
};

#endif // DOTSEATING_H
