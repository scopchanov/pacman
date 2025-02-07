#ifndef SHADOWING_H
#define SHADOWING_H

#include "AbstractPersonality.h"

class Shadowing : public AbstractPersonality
{
	Q_OBJECT
public:
	explicit Shadowing(QObject *parent = nullptr);

	Vector2 calculateTargetPosition() const override;
};

#endif // SHADOWING_H
