#ifndef TELEPORTING_H
#define TELEPORTING_H

#include "AbstractBehavior.h"
#include <QPointF>

class Moving;

class Teleporting : public AbstractBehavior
{
public:
	explicit Teleporting(AbstractComponent *parent = nullptr);

	QPointF destination() const;
	void setDestination(const QPointF &destination);
	int type() const override;

protected:
	void performTasks() override;

private:
	void teleport(AbstractGameObject *gameObject);

	QPointF _destination;
};

#endif // TELEPORTING_H
