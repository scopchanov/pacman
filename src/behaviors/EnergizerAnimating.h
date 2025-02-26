#ifndef ENERGIZERANIMATING_H
#define ENERGIZERANIMATING_H

#include "AbstractAnimatingBehavior.h"

class EnergizerAnimating : public AbstractAnimatingBehavior
{
public:
	explicit EnergizerAnimating(AbstractComponent *parent = nullptr);

	void reset() override;

private:
	void update() override;
};

#endif // ENERGIZERANIMATING_H
