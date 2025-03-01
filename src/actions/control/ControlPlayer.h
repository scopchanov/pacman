#ifndef CONTROLPLAYER_H
#define CONTROLPLAYER_H

#include "AbstractControl.h"

class ControlPlayer : public AbstractControl
{
public:
	explicit ControlPlayer(AbstractComponent *parent = nullptr);

protected:
	void performControlTasks() override;
};

#endif // CONTROLPLAYER_H
