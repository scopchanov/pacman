#ifndef ORIENTATEPLAYER_H
#define ORIENTATEPLAYER_H

#include "AbstractOrientate.h"
#include <QtGlobal>

class Vector2;

class OrientatePlayer : public AbstractOrientate
{
public:
	explicit OrientatePlayer(AbstractComponent *parent = nullptr);

	void reset()  override;

protected:
	void orientate() override;

private:
	qreal directionToAngle(const Vector2 &direction) const;
};

#endif // ORIENTATEPLAYER_H
