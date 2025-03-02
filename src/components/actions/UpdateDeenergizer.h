#ifndef UPDATEDEENERGIZER_H
#define UPDATEDEENERGIZER_H

#include "AbstractAction.h"

class UpdateDeenergizer : public AbstractAction
{
	Q_OBJECT
public:
	explicit UpdateDeenergizer(AbstractComponent *parent = nullptr);

	int type() const override;
	void reset() override;

protected:
	void performTasks() override;

private:
	void updateDeenergizer(qreal len);
	qreal barLength(AbstractComponent *component) const;
};

#endif // UPDATEDEENERGIZER_H
