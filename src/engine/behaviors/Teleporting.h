#ifndef TELEPORTING_H
#define TELEPORTING_H

#include "AbstractBehavior.h"
#include <QPointF>

class CharacterMovement;

class Teleporting : public AbstractBehavior
{
public:
	explicit Teleporting(GameObject *parent = nullptr);

	QPointF destination() const;
	void setDestination(const QPointF &destination);
	int type() const override;

private:
	void performActions() override;
	CharacterMovement *findMovement(GameObject *gameObject) const;

	QPointF m_destination;
};

#endif // TELEPORTING_H
