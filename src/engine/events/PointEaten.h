#ifndef POINTEATEN_H
#define POINTEATEN_H

#include "AbstractGameEvent.h"

class PointEaten : public AbstractGameEvent
{
	Q_OBJECT
public:
	explicit PointEaten(QObject *parent = nullptr);

	void trigger() override;

signals:
	void pointEaten();
};

#endif // POINTEATEN_H
