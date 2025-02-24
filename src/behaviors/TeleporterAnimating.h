#ifndef TELEPORTERANIMATING_H
#define TELEPORTERANIMATING_H

#include "AbstractAnimatingBehavior.h"

class TeleporterAnimating : public AbstractAnimatingBehavior
{
public:
	explicit TeleporterAnimating(AbstractGameObject *parent = nullptr);

	void reset() override;

private:
	void update() override;
};

#endif // TELEPORTERANIMATING_H
