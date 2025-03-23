#ifndef ENERGIZEPLAYER_H
#define ENERGIZEPLAYER_H

#include "AbstractAction.h"

class EnergizePlayer : public AbstractAction
{
	Q_OBJECT
public:
	explicit EnergizePlayer(AbstractComponent *parent = nullptr);

	int type() const override;

protected:
	void performTasks() override;

signals:
	void playerEnergized(const QPointF &position);
};

#endif // ENERGIZEPLAYER_H
