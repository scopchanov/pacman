#ifndef TELEPORT_H
#define TELEPORT_H

#include <QPoint>
#include "AbstractAction.h"

class Teleport : public AbstractAction
{
	Q_OBJECT
public:
	explicit Teleport(AbstractComponent *parent = nullptr);

	QPointF destination() const;
	void setDestination(const QPointF &destination);
	int type() const override;

private:
	void performTasks() override;
	void teleport(AbstractGameObject *gameObject);

	QPointF _destination;
};

#endif // TELEPORT_H
