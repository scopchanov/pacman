#ifndef TELEPORTING_H
#define TELEPORTING_H

#include "AbstractBehavior.h"
#include <QPointF>

class Teleporting : public AbstractBehavior
{
public:
	explicit Teleporting(GameObject *parent = nullptr);

	QPointF destination() const;
	void setDestination(const QPointF &destination);

private:
	void performActions() override;

	QPointF m_destination;
};

#endif // TELEPORTING_H
