#ifndef TELEPORTING_H
#define TELEPORTING_H

#include "AbstractBehavior.h"
#include <QPointF>

class Moving;

class Teleporting : public AbstractBehavior
{
public:
	explicit Teleporting(GameObject *parent = nullptr);

	QPointF destination() const;
	void setDestination(const QPointF &destination);
	int type() const override;

private:
	void performActions() override;
	void teleport(GameObject *gameObject);

	QPointF _destination;
};

#endif // TELEPORTING_H
