#ifndef PLAYERORIENTATE_H
#define PLAYERORIENTATE_H

#include "AbstractOrientate.h"
#include <QtGlobal>

class Vector2;

class PlayerOrientate : public AbstractOrientate
{
public:
	explicit PlayerOrientate(AbstractComponent *parent = nullptr);

	void reset()  override;

private:
	void orientate() override;
	qreal directionToAngle(const Vector2 &direction) const;
};

#endif // PLAYERORIENTATE_H
