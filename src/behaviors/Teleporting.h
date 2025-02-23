#ifndef TELEPORTING_H
#define TELEPORTING_H

#include "AbstractBehavior.h"
#include <QPointF>

class Moving;

class Teleporting : public AbstractBehavior
{
public:
	explicit Teleporting(AbstractGameObject *parent = nullptr);

	QPointF destination() const;
	void setDestination(const QPointF &destination);
	int type() const override;

private:
	void performActions() override;
	void teleport(AbstractGameObject *gameObject);

	QPointF _destination;
};

#endif // TELEPORTING_H
