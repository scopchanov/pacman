#ifndef KILLPLAYER_H
#define KILLPLAYER_H

#include <AbstractAction.h>

class KillPlayer : public AbstractAction
{
	Q_OBJECT
public:
	explicit KillPlayer(AbstractComponent *parent = nullptr);

	int type() const override;

protected:
	void performTasks() override;

signals:
	void playerDied();
};

#endif // KILLPLAYER_H
